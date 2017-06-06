#ifndef NTTEST_H
#define NTTEST_H

// ==========================================================
/*
 *	Header file for normative type test functions.
 *	
 *	These functions test the operation of the normative types:
 *		string
 *		boolean
 *		byte
 *		ubyte
 *		short
 *		ushort
 *		int
 *		uint
 *		long
 *		ulong
 *		float
 *		double
 *		
 *	There is a corresponding testArray function to each
 *	normative type.
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

int genInt();

bool testInt(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testIntArray(
	PvaClientPtr const &pva,
	string const &channel_name);

int genUInt();

bool testUInt(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testUIntArray(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testRecord(
	PvaClientPtr const &pva,
	string const &channel_name,
	string const &record_type);

#endif /* NTTEST_H */
