#ifndef UH_HOST_H
#define UH_HOST_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class Host {
    public:
        Host(map<string, string>);
        Host(const Host &);
        ~Host();

        const string getUrl();
        const string getPassword();
        const string getBindDn();
        const string getBase();

    private:
        string url;
        string password;
        string bindDn;
        string base;
};

#endif
