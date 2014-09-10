#include <ldap.h>
#include <iostream>
#include <assert.h>
#include "host.h"
#include "ldap.h"

using namespace std;

// Standard constructor.
Ldap::Ldap() : host(new Host())
{ 
    assert(host != 0);

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

void Ldap::initialize() {    
    ldap_initialize(&ld, host->getUrl().c_str());
}

void Ldap::set_options() {
    const int option = LDAP_VERSION3;
    ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &option);
}

void Ldap::bind() {
    // Bind to the server. 
    int result = ldap_simple_bind_s(ld, 
                                    host->getBindDn().c_str(), 
                                    host->getPassword().c_str());
    if (result != LDAP_SUCCESS) {
        cerr << "ldap_simple_bind_s: " << ldap_err2string(result) << endl;
        exit(EXIT_FAILURE);
    }
}

void Ldap::unbind() {
    ldap_unbind(ld);
}

void Ldap::search(const string value) {    
    LDAPMessage * answer = searchp(value);
    count_entries(answer);
    print(answer);
    ldap_msgfree(answer);    
}

LDAPMessage * Ldap::searchp(const string value) {
    const string filter = "(|(uid=" + value + ")" 
        + "(mail=" + value + ")" 
        + "(uhuuid=" + value + "))";
    char *attrs[]       = {"uid", "uhuuid", "mail",  NULL};
    const int  attrsonly      = 0;
    LDAPMessage *res;
            
    int result = ldap_search_s(ld, 
                              host->getBase().c_str(), 
                              LDAP_SCOPE_SUBTREE, 
                              filter.c_str(),
                              attrs, 
                              attrsonly, 
                              &res);                         
    if (result != LDAP_SUCCESS) {
        cerr << "ldap_search_s: " << ldap_err2string(result) << endl;
        exit(EXIT_FAILURE);
    }                             

    return res;
}

void Ldap::count_entries(LDAPMessage *answer) {
    // Return the number of objects found during the search.
    int entries_found = ldap_count_entries(ld, answer);
    if (entries_found == 0) {    
        exit(EXIT_FAILURE);
    }
}

void Ldap::print(LDAPMessage *answer) {
    LDAPMessage *entry;
    BerElement *ber;
    char *attribute     = "";
    char **values;
        
    // Cycle through all objects returned with our search.
    for (entry = ldap_first_entry(ld, answer);
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
    cout << ".............................................." << endl;
}
