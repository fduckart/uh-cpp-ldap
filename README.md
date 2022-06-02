[![C++ CI](https://github.com/fduckart/uh-cpp-ldap/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/fduckart/uh-cpp-ldap/actions/workflows/c-cpp.yml)

uh-cpp-ldap
===========

LDAP C++ Demonstration Application

**Overview**

The program demonstrates how to do a simple LDAP search
of the University of Hawaii LDAP service.

This project requires that you specify a password for
the special DN in the program properties file (ldapuh.properties).

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

    $ ./ldapuh duckarts
    uid: duckarts
    uhuuid: 12345678
    mail: duckarts@hawaii.edu
    mail: frank.duckarts@hawaii.edu
    cn: Frank R Duckarts
    ..............................................

    $ ./ldapuh duckarts@hawaii.edu
    uid: duckarts
    uhuuid: 12345678
    mail: duckarts@hawaii.edu
    mail: frank.duckarts@hawaii.edu
    cn: Frank R Duckarts
    ..............................................

    $ ./ldapuh frank.duckarts@hawaii.edu
    uid: duckarts
    uhuuid: 12345678
    mail: duckarts@hawaii.edu
    mail: frank.duckarts@hawaii.edu
    cn: Frank R Duckarts
    ..............................................

**Running the test Bash script**

    $ ./build-and-run-app.bsh
    ..............................................
    Running ldapuh build & run script...
    /usr/bin/g++ -llber -lldap -o ldapuh ldapuh.o ldap.o host.o
    ..............................................
    uid: duckarts
    uhuuid: 12345678
    mail: duckarts@hawaii.edu
    mail: frank.duckarts@hawaii.edu
    cn: Frank R Duckarts
    ..............................................
    uid: duckarts
    uhuuid: 12345678
    mail: duckarts@hawaii.edu
    mail: frank.duckarts@hawaii.edu
    cn: Frank R Duckarts
    ..............................................
    uid: duckarts
    uhuuid: 12345678
    mail: duckarts@hawaii.edu
    mail: frank.duckarts@hawaii.edu
    cn: Frank R Duckarts
    ..............................................
    uid: duckarts
    uhuuid: 12345678
    mail: duckarts@hawaii.edu
    mail: frank.duckarts@hawaii.edu
    cn: Frank R Duckarts
    ..............................................


**Technology**

The program was developed on Apple Mac OS X using
GNU g++ version 4.2.1 and GNU make. There is a test
runner bash script developed on Mac OS X.
