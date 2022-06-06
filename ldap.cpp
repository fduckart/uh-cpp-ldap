#include <assert.h>
#include <fstream>
#include <iostream>
#include <ldap.h>
#include<sstream>
#include<vector>
#include "host.h"
#include "ldap.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

using namespace std;

// Standard constructor.
Ldap::Ldap()
{
    properties = readProperties();
    host = new Host(properties);

    initialize();
    set_options();
    bind();
}

// Host application copy constructor.
Ldap::Ldap(const Ldap & l)
{
    host = l.host;
}

// Destructor.
Ldap::~Ldap()
{
    unbind();

    delete host;
    host = 0;
}

void Ldap::initialize()
{
    ldap_initialize(&ld, host->getUrl().c_str());
}

void Ldap::set_options()
{
    const int option = LDAP_VERSION3;
    ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &option);
}

void Ldap::bind()
{
    BerValue credentials;
    credentials.bv_val = (char*) malloc(host->getPassword().size() * sizeof(char));
    host->getPassword().copy(credentials.bv_val, string::npos);
    credentials.bv_len = host->getPassword().size();

    int result = ldap_sasl_bind_s(ld,
                                  host->getBindDn().c_str(),
                                  LDAP_SASL_SIMPLE,
                                  &credentials,
                                  nullptr, nullptr, nullptr);
    if (result != LDAP_SUCCESS) {
        cerr << "bind error: " << ldap_err2string(result) << endl;
        exit(EXIT_FAILURE);
    }
}

void Ldap::unbind()
{
    ldap_unbind(ld);
}

void Ldap::search(const string value)
{
    LDAPMessage * answer = searchp(value);
    count_entries(answer);
    print(answer);
    ldap_msgfree(answer);
}

vector<char*> Ldap::attributes()
{
    vector<char*>  vc;
    string attrs =  trim(properties["ldapuh.attributes"]);
    if (attrs.size() > 0) {
        vector<string> vs;
        stringstream s_stream(attrs);
        while (s_stream.good()) {
            string substr;
            getline(s_stream, substr, ',');
            vs.push_back(substr);
        }
        transform(vs.begin(), vs.end(), std::back_inserter(vc), convert);
    }
    vc.push_back(NULL);

    return vc;
}

LDAPMessage * Ldap::searchp(const string value)
{
    const string filter = "(|(uid=" + value + ")"
        + "(mail=" + value + ")"
        + "(uhuuid=" + value + "))";

    vector<char*> ats = attributes();
    char **attry = ats.data();
    const int  attrsonly  = 0;
    LDAPMessage *res;

    int result = ldap_search_s(ld,
                              host->getBase().c_str(),
                              LDAP_SCOPE_SUBTREE,
                              filter.c_str(),
                              attry,
                              attrsonly,
                              &res);

    for (size_t i = 0; i < ats.size(); i++) {
        if (ats[i] != NULL) {
            delete [] ats[i];
        }
    }

    if (result != LDAP_SUCCESS) {
        cerr << "ldap_search_s: " << ldap_err2string(result) << endl;
        exit(EXIT_FAILURE);
    }

    return res;
}

void Ldap::count_entries(LDAPMessage *answer)
{
    int entries_found = ldap_count_entries(ld, answer);
    if (entries_found == 0) {
        exit(EXIT_FAILURE);
    }
}

void Ldap::print(LDAPMessage *answer)
{
    BerElement *ber;
    char *attribute = "";
    char **values;

    // Cycle through all objects returned with our search.
    for (LDAPMessage *entry = ldap_first_entry(ld, answer);
         entry != NULL;
         entry = ldap_next_entry(ld, entry)) {
        // Cycle through all returned attributes.
        for (attribute = ldap_first_attribute(ld, entry, &ber);
             attribute != NULL;
             attribute = ldap_next_attribute(ld, entry, ber)) {
            if ((values = ldap_get_values(ld, entry, attribute)) != NULL) {
                // Cycle through all values returned for this attribute.
                for (int i = 0; values[i] != NULL; i++) {
                    cout << attribute << ": " << values[i] << endl;
                }
                ldap_value_free(values);
            }
        }
    }
    cout << ">------------------------------------------------------------<";
    cout << endl;
}

string Ldap::propertiesPath()
{
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    const char *username = pw->pw_name;
    string propertiesPath = string(homedir);
    propertiesPath.append("/.");
    propertiesPath.append(username);
    propertiesPath.append("-conf");
    propertiesPath.append("/ldapuh.properties");

    return propertiesPath;
}

map<string, string> Ldap::readProperties()
{
    map<string, string> propertyMap;

    string filename = propertiesPath();
    vector<string> lines = readFile(filename);
    for (unsigned int i = 0; i < lines.size(); i++) {

        string str(lines[i]);
        string::size_type lastPos = str.size();

        // Find the first '=' character, and then
        // separate the key and value from each other.
        string::size_type pos = str.find_first_of('=', 0);
        if (string::npos != pos || string::npos != lastPos) {
            const string key = trim(str.substr(0, pos));
            string value = trim(str.substr(pos + 1, lastPos));
            propertyMap[key.data()] = value;
        }
    }

    return propertyMap;
}

vector<string> Ldap::readFile(string filename)
{
    ifstream inFile(filename.data(), ios::in);
    if (!inFile) {
        cerr << "File '" << filename << "' could not be opened.\n";
        exit(1);
    }

    vector<string> lines;
    string line;
    while (inFile && !inFile.eof()) {
        getline(inFile, line);
        line = trim(line);
        int len = line.size();
        if (len > 1) {
            lines.push_back(line.substr(0, line.size()));
        }
    }

    inFile.close();

    return lines;
}

const string Ldap::trim(const string& s)
{
    if (s.length() == 0)
        return s;

    int f = s.find_first_not_of(" \t");  // Find first char.
    int e = s.find_last_not_of(" \t");   // Find ending char.

    if (e == -1)
        return "";  // Didn't find any chars.

    return string(s, f, e - f + 1);  // Trim off spaces.
}

char * Ldap::convert(const string & s)
{
    char *pc = new char[s.size()+1];
    std::strcpy(pc, s.c_str());

    return pc;
}
