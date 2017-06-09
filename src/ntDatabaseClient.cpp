/*
 * =======================================================================
 * 
 * 	Author: Evan Smith
 * 	Date  : 6/5/2017
 *
 * 	ntDatabaseClient.cpp
 *
 * 	Source file for client side of normative type database test program.
 *
 *	This program primarily serves as an example on how to access and manipulate
 *	these normative types when they are held in pvDatabase hosted pvRecords.
 *
 *	The most used scalar values are strings, shorts, long ints, and doubles. 
 *	So we will be writing to and reading from these scalar normative type records. 
 *	We will also be "testing" for data consistency by comparing the written 
 *	and read information. These do not constitute thorough tests and are
 *	only meant to demonstrate how to read and write from the records.
 *
 * 	NOTE: for the sake of brevity, normative type will henceforth be referred to 
 * 	      as 'nt'.
 *
 * =======================================================================
 */

#include <iomanip>
#include <iostream>
#include <memory>
#include <time.h>
#include <vector>

#include "ntTest.h"
#include "ntScalarTest.h"

#include <pv/pvAccess.h>
#include <pv/pvaClient.h>
#include <pv/pvData.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvaClient;

int main (int argc, char **argv)
{
	bool verbosity(false);
	bool debug(false);
	
	// Handle program flags.
	if (argc > 1 && argv[1] != NULL) {
		string arg(argv[1]);
		if (arg == "-v") {
		
			verbosity = true;		
		
		} else if (arg == "-h") {
			
			cout << "Help -- executable flags\n"
			     << "\t-v (vebose. prints test information)\n"
				 << "\t-d (debug. prints debug information)\n"
				 << "\t-h (help. prints help information)\n";
			return 0;
		
		} else if (arg == "-d") {
		
			debug = true;
		
		} else {
			
			cout << "Unrecognized option: '" << arg
			     << "'. ('ntDatabaseClient -h' for help.)\n"; 
			return 1;
		
		}
	}
	
	cout << "ntDatabase Client\n";
	string types[] = {"string", "short", "int", "long", "double"};
	int test_num = 5;
	try {
	
		PvaClientPtr pvaClient = PvaClient::get("pva");
		cout << "debug : " << (debug ? "true" : "false") << endl;
		if (debug) PvaClient::setDebug(true);
		// seed rand for the generator functions in the test code.
		srand(time(NULL));

		bool result;
		string channel_name;

		// Test the scalar and scalar array nt records.
		for (int i = 0; i < test_num; ++i)
		{
			channel_name = types[i];
			result = testScalarRecord(verbosity, pvaClient, channel_name, types[i]);
			if (result)
			{
				cout << channel_name << " record test successful\n";
			}
			else 
			{
				cout << channel_name << " record test unsuccessful\n";
			}

			channel_name += "Array";
			result = testScalarRecord(verbosity, pvaClient, channel_name, types[i]);
			if (result)
			{
				cout << channel_name << " record test successful\n";
			}
			else 
			{
				cout << channel_name << " record test unsuccessful\n";
			}

			result = false;
			channel_name.clear();
		}
		// Test the more specific nt records.	
		channel_name = "enum";
		result = testEnum(verbosity, pvaClient, channel_name);	
		if (result)
		{
			cout << channel_name << " record test successful\n";
		}
		else 
		{
			cout << channel_name << " record test unsuccessful\n";
		}
		
		channel_name = "matrix";
		result = testMatrix(verbosity, pvaClient, channel_name);	
		if (result)
		{
			cout << channel_name << " record test successful\n";
		}
		else 
		{
			cout << channel_name << " record test unsuccessful\n";
		}
		// Uniform Resouce Identifier 
		channel_name = "uri";
		result = testURI(verbosity, pvaClient, channel_name);	
		if (result)
		{
			cout << channel_name << " record test successful\n";
		}
		else 
		{
			cout << channel_name << " record test unsuccessful\n";
		}
		
		channel_name = "name_value";
		result = testNameValue(verbosity, pvaClient, channel_name);	
		if (result)
		{
			cout << channel_name << " record test successful\n";
		}
		else 
		{
			cout << channel_name << " record test unsuccessful\n";
		}
		
		channel_name = "table";
		result = testTable(verbosity, pvaClient, channel_name);	
		if (result)
		{
			cout << channel_name << " record test successful\n";
		}
		else 
		{
			cout << channel_name << " record test unsuccessful\n";
		}
		
		channel_name = "attribute";
		result = testAttribute(verbosity, pvaClient, channel_name);	
		if (result)
		{
			cout << channel_name << " record test successful\n";
		}
		else 
		{
			cout << channel_name << " record test unsuccessful\n";
		}

		channel_name = "multi_channel";
		result = testMultiChannel(verbosity, pvaClient, channel_name);	
		if (result)
		{
			cout << channel_name << " record test successful\n";
		}
		else 
		{
			cout << channel_name << " record test unsuccessful\n";
		}
	
	} catch (std::runtime_error e) {
		
		cerr << "exception: " << e.what() << endl;
		return -1;
	
	}

	return 0;
}

