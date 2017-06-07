#ifndef NTTEST_H
#define NTTEST_H

// ==========================================================
/*
 *	Header file for normative type test functions.
 *	
 *	These functions test the operation of some scalar normative types:
 *		string
 *		short
 *		int
 *		long
 *		double
 *		
 *	There is a corresponding testArray function to each
 *	scalar type.
 *
 */
// ==========================================================

#include <pv/pvAccess.h>
#include <pv/pvaClient.h>
#include <pv/pvData.h>
#include <pv/channelProviderLocal.h>
#include <pv/serverContext.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvaClient;

string genString();

bool testString(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testStringArray(
	PvaClientPtr const &pva,
	string const &channel_name);

long genInt(long low, long high);

bool testInt(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testIntArray(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testLong(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testLongArray(
	PvaClientPtr const &pva,
	string const &channel_name);

double genDouble();

bool testRecord(
	bool const &verbosity,
	PvaClientPtr const &pva,
	string const &channel_name,
	string const &record_type);

#endif /* NTTEST_H */
