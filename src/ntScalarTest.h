#ifndef NTSCALARTEST_H
#define NTSCALARTEST_H

/*
 * ==========================================================
 *	Header file for scalar normative type test functions.
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
 *	The test functions work by writing a value to the record, reading
 *	the value, and then comparing the two values to check for consistency.
 *
 *	These do not serve as intensive tests, but instead are examples to 
 *	demonstrate the functionality of the scalar normative types.
 *
 * ==========================================================
 */

#include <pv/pvAccess.h>
#include <pv/pvaClient.h>
#include <pv/pvData.h>
#include <pv/channelProviderLocal.h>
#include <pv/serverContext.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvaClient;

// Generates a string of "random" length and "random" alpha-numeric content.
string genString();

bool testString(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testStringArray(
	PvaClientPtr const &pva,
	string const &channel_name);

// Generates a "random" integer in the range 0 to high.
long genInt(long high);

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

// Generates a "random" floating point number.
double genDouble();

bool testScalarRecord(
	bool const &verbosity,
	PvaClientPtr const &pva,
	string const &channel_name,
	string const &record_type);

#endif /* NTSCALARTEST_H */
