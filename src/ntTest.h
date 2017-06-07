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

bool genBool();

bool testBool(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testBoolArray(
	PvaClientPtr const &pva,
	string const &channel_name);

char genByte();

bool testByte(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testByteArray(
	PvaClientPtr const &pva,
	string const &channel_name);

int genInt();

bool testInt(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testIntArray(
	PvaClientPtr const &pva,
	string const &channel_name);

unsigned int genUInt();

bool testUInt(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testUIntArray(
	PvaClientPtr const &pva,
	string const &channel_name);

long genLong();

bool testLong(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testLongArray(
	PvaClientPtr const &pva,
	string const &channel_name);

unsigned long genULong();

bool testULong(
	PvaClientPtr const &pva,
	string const &channel_name);

bool testULongArray(
	PvaClientPtr const &pva,
	string const &channel_name);


bool testRecord(
	bool const &verbosity,
	PvaClientPtr const &pva,
	string const &channel_name,
	string const &record_type);

#endif /* NTTEST_H */
