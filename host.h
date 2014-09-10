#ifndef UH_HOST_H
#define UH_HOST_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class Host {
    public:
        Host(); 
        Host(const Host &);
        ~Host();

        void readProperties();
        
        const string getUrl();
        const string getPassword();
        const string getBindDn();
        const string getBase();
    
    private:
        string url;
        string password;
        string bindDn;
        string base;  
        
        vector<string> readFile(string);
        map<string, string> getFieldValueMap(string);
        const string trim(const string& s);
};

#endif
