// =============================================================
/*
 * =============================================================
 * 	Author: Evan Smith
 * 	Date  : 6/5/2017
 *
 * 	ntDatabase.cpp
 *
 *	Source file that implements the creation of the normative
 *	type database.
 *
 * =============================================================
 */

// Located in local pv directory.
#include <pv/ntDatabase.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <pv/standardField.h>
#include <pv/standardPVField.h>
#include <pv/channelProviderLocal.h>
#include <pv/serverContext.h>
#include <pv/ntscalar.h>
#include <pv/ntscalarArray.h>
#include <pv/ntenum.h>

using namespace std;
using std::tr1::static_pointer_cast;
using namespace epics::pvData;
using namespace epics::nt;
using namespace epics::pvDatabase;
using namespace epics::pvAccess;
// Defined locally in pv/ntDatabase.h
using namespace epics::ntDatabase;

// Global definitions of singleton builder classes
static FieldCreatePtr         fieldCreate = getFieldCreate();
static StandardFieldPtr     standardField = getStandardField();
static PVDataCreatePtr       pvDataCreate = getPVDataCreate();
static StandardPVFieldPtr standardPVField = getStandardPVField();

// Generic record creation function.
// NOTE:
// By doing it this way you can create a record of any applicable scalar type 
// with a single function. By modifying it slightly with another argument or 
// some extra logic to examine the passed recordName (assuming an array records
// name will have array in it), you could create a function that creates a scalar 
// record OR a scalar array record instead of always both.
//
// Credit for this idea goes to Marty Kraimer at ANL
static void createRecords(
	PVDatabasePtr const &master,
	ScalarType scalarType,
	string const &recordNamePrefix)
{
	string recordName = recordNamePrefix;
	
	NTScalarBuilderPtr ntScalarBuilder = NTScalar::createBuilder();
	
	PVStructurePtr pvStructure = ntScalarBuilder->
		value(scalarType)->
		addAlarm()->
		addTimeStamp()->
		createPVStructure();
	
	PVRecordPtr pvRecord = PVRecord::create(recordName, pvStructure);
	
	bool result = master->addRecord(pvRecord);
	if (!result) cerr << "Failed to add record " << recordName << " to database\n";

	recordName += "Array";

	NTScalarArrayBuilderPtr ntScalarArrayBuilder = NTScalarArray::createBuilder();
	pvStructure = ntScalarArrayBuilder->
		value(scalarType)->
		addAlarm()->
		addTimeStamp()->
		createPVStructure();
	
	pvRecord = PVRecord::create(recordName, pvStructure);

	result = master->addRecord(pvRecord);
	if (!result) cerr << "Failed to add record " << recordName << " to database\n";

	return;
}

// Create function creates and adds records to database.
void NTDatabase::create()
{

	PVDatabasePtr master = PVDatabase::getMaster();
	// Create string and stringArray records.	
	createRecords(master, pvString, "string");
	// Create numeric types and numeric type arrays.
	createRecords(master, pvInt, "int");

	return;
}

// =============================================================
