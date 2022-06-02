#include <iostream>
#include <assert.h>
#include "ldap.h"

using namespace std;

// Main function.
int main(int argc, char* argv[])
{
    if (argc == 1) {
        cout << "usage: ldapuh uid" << endl;
        return EXIT_FAILURE;
    }

    Ldap ldap;
    ldap.search(argv[1]);

    return EXIT_SUCCESS;
}
