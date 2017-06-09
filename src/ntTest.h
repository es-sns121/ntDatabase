#ifndef NTTEST_H
#define NTTEST_H

/*
 * ==========================================================
 *	ntTest.h
 *
 *	Header file for normative type test and demonstration functions.
 *	
 *	These functions test the operation of some normative types:
 *		NTEnum   (enumerated)
 *		NTMatrix (matrix of real numbers)
 *      NTURI (Uniform Resource Identifier)
 *      NTNameValue (Name and value association)
 *      NTTable
 *      NTAttribute (Name and associate value)
 *      NTMultiChannel (Aggregate structure of multiple channel
 *      			    names and values)
 *
 * 		These do not serve as intensive tests, but instead aim
 * 		to demonstrate the methods of interacting with the 
 * 		records and to demonstrate the functionality of the 
 * 		normative types.
 * 		
 * 		The methods of testing vary, but involve one or both of 
 * 		the following:
 * 			Writing data to the record.
 * 			Reading data from the record.
 * 		In the cases where both occur, a further test looking
 * 		for data consistency in the writes and reads is done.
 *
 * ==========================================================
 */

#include <iostream>
#include <sstream>
#include <pv/pvAccess.h>
#include <pv/pvaClient.h>
#include <pv/pvData.h>
#include <pv/channelProviderLocal.h>
#include <pv/serverContext.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvaClient;

bool testEnum(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool testMatrix(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool testURI(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool testNameValue(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool testTable(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool testAttribute(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool testMultiChannel(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

#endif /* NTTEST_H */
