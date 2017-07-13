#ifndef NTSCALARDEMO_H
#define NTSCALARDEMO_H

/*
 * ==========================================================
 *	Header file for scalar normative type demo functions.
 *	
 *	These functions demo the operation of some scalar normative types:
 *		string
 *		short
 *		int
 *		long
 *		double
 *		
 *	There is a corresponding demo*Array function to each
 *	scalar type.
 *	
 *	The functions work by writing a value to the record, reading
 *	the value, and then comparing the two values to check for consistency.
 *
 * ==========================================================
 */


#include <map>
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

bool demoString(
	bool verbosity,
	PvaClientChannelPtr channel);

bool demoStringArray(
	bool verbosity,
	PvaClientChannelPtr channel);

// Generates a "random" integer in the range 0 to high.
long genInt(long high);

bool demoShort(
	bool verbosity,
	PvaClientChannelPtr channel);

bool demoShortArray(
	bool verbosity,
	PvaClientChannelPtr channel);

bool demoInt(
	bool verbosity,
	PvaClientChannelPtr channel);

bool demoIntArray(
	bool verbosity,
	PvaClientChannelPtr channel);

bool demoLong(
	bool verbosity,
	PvaClientChannelPtr channel);

bool demoLongArray(
	bool verbosity,
	PvaClientChannelPtr channel);

// Generates a "random" floating point number.
double genDouble();

bool demoDouble(
	bool verbosity,
	PvaClientChannelPtr channel);

bool demoDoubleArray(
	bool verbosity,
	PvaClientChannelPtr channel);

#endif /* NTSCALARDEMO_H */
