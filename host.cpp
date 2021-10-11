#include <fstream>
#include <iostream>
#include "host.h"

using namespace std;

// Standard constructor.
Host::Host()
{
    string filename = "ldapuh.properties";
    map<string, string> values = getFieldValueMap(filename);

    url = values["ldapuh.url"];
    password = values["ldapuh.password"];
    bindDn = values["ldapuh.bindDn"];
    base = values["ldapuh.base"];
}

// Host application copy constructor.
Host::Host(const Host & l)
{
    url = l.url;
    password = l.password;
    bindDn = l.bindDn;
    base = l.base;
}

// Destructor.
Host::~Host()
{
    // Empty, so far.
}

map<string, string> Host::getFieldValueMap(string fileName)
{
    map<string, string> fieldValueMap;

    vector<string> lines = readFile(fileName);
    for (unsigned int i = 0; i < lines.size(); i++) {

        string str(lines[i]);
        string::size_type lastPos = str.size();

        // Find the first '=' character, and then
        // separate the field and value from each other.
        string::size_type pos = str.find_first_of('=', 0);
        if (string::npos != pos || string::npos != lastPos) {
            const string field = trim(str.substr(0, pos));
            string value = trim(str.substr(pos + 1, lastPos));
            fieldValueMap[field.data()] = value;
        }
    }

    return fieldValueMap;
}

vector<string> Host::readFile(string fileName)
{
    ifstream inFile(fileName.data(), ios::in);
    if (!inFile) {
        cerr << "File could not be opened..\n";
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

const string Host::trim(const string& s)
{
    if (s.length() == 0)
        return s;

    int f = s.find_first_not_of(" \t");  // Find first char.
    int e = s.find_last_not_of(" \t");   // Find ending char.

    if (e == -1)
        return "";  // Didn't find any chars.

    return string(s, f, e - f + 1);  // Trim off spaces.
}

const string Host::getUrl()
{
    return url;
}

const string Host::getPassword()
{
    return password;
}

const string Host::getBindDn()
{
    return bindDn;
}

const string Host::getBase()
{
    return base;
}
