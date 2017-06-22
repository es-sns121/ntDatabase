# ntDatabase

This example provides an EPICS V4 database that hosts EPICS V4 PVRecords. 
The records hold normative type pvData structures.
The client program will connect to the database and then perform some
demonstrations on how to interact with the records.

## Building

If a proper RELEASE.local file exists two directory levels above **ntDatabase**,
or in **ntDatabase/configure/RELEASE.local** then just type:

    make

It can also be built by:

    cp configure/ExampleRELEASE.local configure/RELEASE.local
    edit file configure/RELEASE.local
    make

## To start the database as a standalone main

    > pwd
    /home/Epics/EPICS-CPP-4.5.0/ntDatabase/
    > bin/$EPICS_HOST_ARCH/ntDatabaseMain

## OR
    > pwd
    /home/Epics/EPICS-CPP-4.5.0/ntDatabase/
	> serverRunner

## To start the client program

    > pwd
    /home/Epics/EPICS-CPP-4.5.0/ntDatabase/
    > bin/$EPICS_HOST_ARCH/ntDatabaseclient

## OR
    > pwd
    /home/Epics/EPICS-CPP-4.5.0/ntDatabase/
	> clientRunner

## ntDatabase/src/pv

This directory has the following files:

     ntDatabase.h
  

## ntDatabase/src

This directory has the following files:

* ntDatabaseClient.cpp  

Code for a client program that uses pvaClient to access the records
hosted on the database.

* ntScalarDemo.h

* ntScalarDemo.cpp

Code that demonstrates the functionality of the scalar normative types
and provides examples on operating on them.

* ntDemo.h

* ntDemo.cpp

Code that demonstrates the functionality of the non-scalar normative types
and provides examples on operating on them.

* ntDatabase.cpp 

Code that creates many PVRecords.    

* ntDatabaseMain.cpp

Code that allows the PVRecords to be available via a standalone main program.

