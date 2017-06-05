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
// Defined in pv/ntDatabase.h
using namespace epics::ntDatabase;

// Glocal definitions of singleton builder classes
static FieldCreatePtr         fieldCreate = getFieldCreate();
static StandardFieldPtr     standardField = getStandardField();
static PVDataCreatePtr       pvDataCreate = getPVDataCreate();
static StandardPVFieldPtr standardPVField = getStandardPVField();

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

void NTDatabase::create()
{

	PVDatabasePtr master = PVDatabase::getMaster();
	
	createRecords(master, pvString, "string01");

	// bool result(false);
	
	return;
}

// =============================================================
