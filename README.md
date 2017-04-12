uh-cpp-ldap
===========

LDAP C++ Demonstration Application

**Overview**

The program demonstrates how to do a simple LDAP search
of the University of Hawaii LDAP service.

This project uses the test server and requires that you
specify a password for the special DN in the program
properties file (ldapuh.properties). The 'filedrop'
special DN is specified in the properties and should
most likey be changed to whatever one you want to use.

**Technology**

The program was developed on Apple Mac OS X using
GNU g++ version 4.2.1 and GNU make. There is a test
runner bash script developed on Mac OS X.

**Building the Program**

    $ make all

**Cleaning up**

    $ make clean

**Running the program**

Here are the commands (and their output)
that you can use to run the program:

    $ make all
    /usr/bin/g++ -Wno-write-strings -g -Wall -c  ldapuh.cpp
    /usr/bin/g++ -Wno-write-strings -g -Wall -c  ldap.cpp
    /usr/bin/g++ -Wno-write-strings -g -Wall -c  host.cpp
    /usr/bin/g++ -llber -lldap -o ldapuh ldapuh.o ldap.o host.o

    $ ./ldapuh duckart
    uid: duckart
    uhuuid: 12345678
    mail: duckart@hawaii.edu
    mail: frank.duckart@hawaii.edu
    ..............................................

    $ ./ldapuh duckart@hawaii.edu
    uid: duckart
    uhuuid: 12345678
    mail: duckart@hawaii.edu
    mail: frank.duckart@hawaii.edu
    ..............................................

    $ ./ldapuh frank.duckart@hawaii.edu
    uid: duckart
    uhuuid: 12345678
    mail: duckart@hawaii.edu
    mail: frank.duckart@hawaii.edu
    ..............................................

**Running the test Bash script**

    $ ./build-and-run-app.bsh
    ..............................................
    Running ldapuh build & run script...
    /usr/bin/g++ -llber -lldap -o ldapuh ldapuh.o ldap.o host.o
    ..............................................
    uid: duckart
    uhuuid: 12345678
    mail: duckart@hawaii.edu
    mail: frank.duckart@hawaii.edu
    ..............................................
    uid: duckart
    uhuuid: 12345678
    mail: duckart@hawaii.edu
    mail: frank.duckart@hawaii.edu
    ..............................................
    uid: duckart
    uhuuid: 12345678
    mail: duckart@hawaii.edu
    mail: frank.duckart@hawaii.edu
    ..............................................
    uid: duckart
    uhuuid: 12345678
    mail: duckart@hawaii.edu
    mail: frank.duckart@hawaii.edu
    ..............................................
