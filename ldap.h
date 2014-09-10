#ifndef UH_LDAPER_H
#define UH_LDAPER_H

#include <string>
#include <ldap.h>
#include "host.h"

using namespace std;

class Ldap {
    public:
        Ldap(); 
        Ldap(const Ldap &);
        ~Ldap();
      
        void search(const string);
      
    private:  
        Host * host;
        LDAP * ld;
        
        void initialize();
        void set_options();
        void bind();      
        void unbind();
        LDAPMessage * searchp(const string);    
        void count_entries(LDAPMessage *);
        void print(LDAPMessage *);
};

#endif
