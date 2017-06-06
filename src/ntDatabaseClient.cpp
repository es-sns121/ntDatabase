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

#include <pv/pvAccess.h>
#include <pv/pvaClient.h>
#include <pv/pvData.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvaClient;

int main (int argc, char **argv)
{
	cout << "ntDatabase Client\n";
	string types[] = {"string", "byte", "ubyte", "short", "ushort", "int", "uint", "long", "ulong"};
	int test_num = 9;
	try {
	
		PvaClientPtr pvaClient = PvaClient::get("pva");
		// add debug option
	
		srand(time(NULL));

		bool result;
		string channel_name;
		for (int i = 0; i < test_num; ++i)
		{
			channel_name = types[i];
			result = testRecord(pvaClient, channel_name, types[i]);
			if (result)
			{
				cout << "Record test successful\n";
			}
			else 
			{
				cout << "Record test unsuccessful\n";
			}

			channel_name += "Array";
			result = testRecord(pvaClient, channel_name, types[i]);
			if (result)
			{
				cout << "Record test successful\n";
			}
			else 
			{
				cout << "Record test unsuccessful\n";
			}

			result = false;
			channel_name.clear();
		}
	} catch (std::runtime_error e) {
		
		cerr << "exception: " << e.what() << endl;
		return -1;
	
	}

	return 0;
}

// =======================================================================
