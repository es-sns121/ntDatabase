#ifndef NTTEST_H
#define NTTEST_H

// ==========================================================
/*
 *	Header file for normative type test functions.
 *	
 *	These functions test the operation of some normative types:
 *		NTEnum   (enumerated)
 *		NTMatrix (matrix of real numbers)
 *
 */
// ==========================================================

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

#endif /* NTTEST_H */
