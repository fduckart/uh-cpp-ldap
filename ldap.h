#ifndef UH_LDAPER_H
#define UH_LDAPER_H

#include <map>
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
        map<string, string> properties;

        void initialize();
        void set_options();
        void bind();
        void unbind();
        LDAPMessage * searchp(const string);
        void count_entries(LDAPMessage *);
        void print(LDAPMessage *);

        string propertiesPath();
        map<string, string> readProperties();
        vector<string> readFile(string);
        const string trim(const string& s);
        static char *convert(const std::string & s);
        vector<char*> attributes();
};

#endif
