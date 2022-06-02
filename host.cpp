#include "host.h"

using namespace std;

// Constructor.
Host::Host(map<string, string> values)
{
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
