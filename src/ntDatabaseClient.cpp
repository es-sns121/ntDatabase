/*
 * =======================================================================
 * 
 * 	Author: Evan Smith
 * 	Date  : 6/5/2017
 *
 * 	ntDatabaseClient.cpp
 *
 * 	Source file for client side of normative type database demonstration program.
 *
 *	This program primarily serves as an example on how to access and manipulate
 *	these normative types when they are held in pvDatabase hosted pvRecords.
 *
 *	The most used scalar values are strings, shorts, long ints, and doubles. 
 *	So we will be writing to and reading from these scalar normative type records. 
 *	We will also be "demoing" for data consistency by comparing the written 
 *	and read information to demonstrate how to read and write from the records.
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

#include "ntDemo.h"
#include "ntScalarDemo.h"

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
			
			cout << "Help -- executable flags -- only one accepted at a time\n"
			     << "\t-v (verbose. prints demo ouput. Recommend redirecting to a file.)\n"
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
	int demo_num = 5;
	try {
	
		PvaClientPtr pvaClient = PvaClient::get("pva");
		
		cout << "debug : " << (debug ? "true" : "false") << endl;
		if (debug) PvaClient::setDebug(true);
		
		// seed rand for the generator functions in the demo code.
		srand(time(NULL));

		bool result(false);
		string channel_name;

		// TODO: Find a poymorphic way of doing this.

		// Demo the scalar and scalar array nt records.
		for (int i = 0; i < demo_num; ++i) {
			channel_name = types[i];
			result = demoScalarRecord(verbosity, pvaClient, channel_name);
			printResult(result, channel_name);

			result = false;
			channel_name.clear();
		}
		
		/* =============================================================
				Demo the more specific nt records.	
		*/

		/* NTEnum */
		channel_name = "enum";
		demoRecord(verbosity, pvaClient, channel_name);	

		/* NTMatrix */
		channel_name = "matrix";
		demoRecord(verbosity, pvaClient, channel_name);	
		
		/* NTURI (Uniform Resouce Identifier) */ 
		channel_name = "uri";
		demoRecord(verbosity, pvaClient, channel_name);	
		
		/* NTNameValue */
		channel_name = "name_value";
		demoRecord(verbosity, pvaClient, channel_name);	
		
		/* NTTable */
		channel_name = "table";
		demoRecord(verbosity, pvaClient, channel_name);	
	
		/* NTAttribute */
		channel_name = "attribute";
		demoRecord(verbosity, pvaClient, channel_name);	

		/* NTMultiChannel */
		channel_name = "multi_channel";
		demoRecord(verbosity, pvaClient, channel_name);	
	
	} catch (std::runtime_error e) {	
		cerr << "exception: " << e.what() << endl;
		return -1;
	}

	return 0;
}

