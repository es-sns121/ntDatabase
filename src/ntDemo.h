#ifndef NTDEMO_H
#define NTDEMO_H

/*
 * ==========================================================
 *	ntDemo.h
 *
 *	Header file for normative type demonstration functions.
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
 * 		These functions aim to demonstrate the methods of interacting 
 * 		with the records and to demonstrate the functionality of the 
 * 		normative types.
 * 		
 * 		The methods of demoing vary, but involve one or both of 
 * 		the following:
 * 			Writing data to the record.
 * 			Reading data from the record.
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

void printResult(const bool &result, const string &channel_name);

int demoRecord(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name);

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

#endif /* NTDEMO_H */
