# Build program.

# Set the compiler
CC = /usr/bin/g++

# Compiler flags
CFLAGS = -Wno-write-strings -g -Wall -c 

# Linker flags 
LDFLAGS = -llber -lldap -o

PROG0 = ldapuh

ALL_PROGRAMS = $(PROG0)  

# Source files.
PROG00_OBJS = ldapuh.o
PROG01_OBJS = ldap.o
PROG02_OBJS = host.o

# Header files.
SOURCE_HDRS = host.h ldap.h

# FIRST RULE: Build everything
all:		$(ALL_PROGRAMS)

# Rule to build program.  This is the main application.
$(PROG0):	$(PROG00_OBJS) $(PROG01_OBJS) $(PROG02_OBJS)
		$(CC) $(LDFLAGS) $@ $^


# This rule defines how to build any .o file
# from its corresponding .cpp file
%.o:		%.cpp $(SOURCE_HDRS)
		$(CC) $(CFLAGS) $<


# Clean up - note, no dependency,
# if this rule is called always do it
clean:
		rm -f *.o ~* $(ALL_PROGRAMS)

