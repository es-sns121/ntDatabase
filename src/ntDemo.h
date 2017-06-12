#ifndef NTTEST_H
#define NTTEST_H

/*
 * ==========================================================
 *	ntTest.h
 *
 *	Header file for normative type demo and demonstration functions.
 *	
 *	These functions demo the operation of some normative types:
 *		NTEnum   (enumerated)
 *		NTMatrix (matrix of real numbers)
 *      NTURI (Uniform Resource Identifier)
 *      NTNameValue (Name and value association)
 *      NTTable
 *      NTAttribute (Name and associate value)
 *      NTMultiChannel (Aggregate structure of multiple channel
 *      			    names and values)
 *
 * 		These do not serve as intensive demos, but instead aim
 * 		to demonstrate the methods of interacting with the 
 * 		records and to demonstrate the functionality of the 
 * 		normative types.
 * 		
 * 		The methods of demoing vary, but involve one or both of 
 * 		the following:
 * 			Writing data to the record.
 * 			Reading data from the record.
 * 		In the cases where both occur, a further demo looking
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

bool demoEnum(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool demoMatrix(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool demoURI(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool demoNameValue(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool demoTable(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool demoAttribute(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

bool demoMultiChannel(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);	

#endif /* NTTEST_H */
