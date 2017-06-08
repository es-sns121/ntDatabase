// =======================================================================
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
 *	Each normative type and its associated array record is tested. It is 
 *	written to, and then read from to check for data consistency. 
 *	
 *	This program also serves as an example on how to access and manipulate
 *	these records.
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

	if (argc > 1 && argv[1] != NULL) 
	{
		string arg(argv[1]);
		if (arg == "-v") 
		{
			// Set the verbosity flag.	
			verbosity = true;		
		}
		else if (arg == "-h")
		{
			cout << "Help not yet implemented. Try again later." << endl;
			return 0;
		}
		else
		{
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
		// add debug option
	
		srand(time(NULL));

		bool result;
		string channel_name;
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

	} catch (std::runtime_error e) {
		
		cerr << "exception: " << e.what() << endl;
		return -1;
	
	}

	return 0;
}

// =======================================================================
