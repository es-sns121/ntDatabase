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
	
	// Handle executable flag.
	if (argc > 1 && argv[1] != NULL) {
		string arg(argv[1]);
		if (arg == "-v") {
		
			verbosity = true;		
	
	/* Help flag */
		} else if (arg == "-h") {
			
			cout << "Help -- executable flags -- only one accepted at a time\n"
			     << "\t-v (verbose. prints demo ouput. Recommend redirecting to a file.)\n"
				 << "\t-d (debug. prints debug information)\n"
				 << "\t-h (help. prints help information)\n";
			return 0;
	
	/* Debug flag */
		} else if (arg == "-d") {
		
			debug = true;
		
	/* Error */
		} else {
			
			cout << "Unrecognized option: '" << arg
			     << "'. ('ntDatabaseClient -h' for help.)\n"; 
			return 1;
		
		}
	}
	
	cout << "ntDatabase Client\n";
	
	string record_types[] = {
					  "string", "short", "int", "long", "double",      // Scalar nt examples.
					  
					  "enum", "matrix", "uri", "name_value", "table",  // More specific nt examples
					  "attribute", "multi_channel"};                 
	
	int number_of_record_types = 12;
	
	try {
	
		PvaClientPtr pvaClient = PvaClient::get("pva");
		
		cout << "debug : " << (debug ? "true" : "false") << endl;
		
		if (debug) PvaClient::setDebug(true);
		
		// seed rand for the generator functions in the demo code.
		srand(time(NULL));

		string channel_name;

		// Demo the nt records.
		for (int i = 0; i < number_of_record_types; ++i) {
			
			channel_name = record_types[i];
			
			demoRecord(verbosity, pvaClient, channel_name);

			channel_name.clear();
		}
	
	} catch (std::runtime_error e) {	
		cerr << "exception: " << e.what() << endl;
		return -1;
	}

	return 0;
}

