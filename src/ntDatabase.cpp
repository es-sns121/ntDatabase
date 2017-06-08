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
#include <pv/ntmatrix.h>
#include <pv/nturi.h>
#include <pv/ntnameValue.h>
#include <pv/nttable.h>

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
static void createScalarRecords(
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

// Creates and adds records to database.
void NTDatabase::create()
{
	bool result(false);

	// Get the database hosted by the local provider.
	PVDatabasePtr master = PVDatabase::getMaster();
	
	// Create string and stringArray records.	
	createScalarRecords(master, pvString, "string");
	// Create numeric type and numeric type array records.
	createScalarRecords(master, pvShort, "short");
	createScalarRecords(master, pvInt, "int");
	createScalarRecords(master, pvLong, "long");
	createScalarRecords(master, pvDouble, "double");
	
	/* ===================================================== */
	// Create a NTEnum pvrecord.
	
	NTEnumBuilderPtr ntEnumBuilder = NTEnum::createBuilder();
	
	PVStructurePtr pvStructure = ntEnumBuilder->
		addAlarm()->
		addTimeStamp()->
		createPVStructure();
	shared_vector<string> choices(2);
	choices[0] = "zero";
	choices[1] = "one";
	PVStringArrayPtr pvChoices = pvStructure->getSubField<PVStringArray>("value.choices");
	pvChoices->replace(freeze(choices));
	result = master->addRecord(PVRecord::create("enum", pvStructure));
	if (!result) cerr << "Failed to add enum record\n";

	/* ===================================================== */
	// Create a NTMatrix pvrecord.
	
	NTMatrixBuilderPtr ntMatrixBuilder = NTMatrix::createBuilder();
	
	pvStructure = ntMatrixBuilder->
		addDim()->          // Adds dimension field to the matrix. This will define the number 
							// of columns and rows in the matrix.
		addAlarm()->
		addTimeStamp()->
		createPVStructure();
	result = master->addRecord(PVRecord::create("matrix", pvStructure));
	if (!result) cerr << "Failed to add matrix record\n";
	
	/* ===================================================== */
	// Create a NTURI pvrecord.
	
	NTURIBuilderPtr ntURIBuilder = NTURI::createBuilder();
	
	pvStructure = ntURIBuilder->
		addQueryString("query")->
		createPVStructure();
	result = master->addRecord(PVRecord::create("uri", pvStructure));
	if (!result) cerr << "Failed to add uri record\n";
	
	/* ===================================================== */
	// Create a NTNameValue pvrecord.
	
	NTNameValueBuilderPtr ntNameValueBuilder = NTNameValue::createBuilder();
	
	pvStructure = ntNameValueBuilder->
		value(pvDouble)->
		createPVStructure();
	result = master->addRecord(PVRecord::create("name_value", pvStructure));
	if (!result) cerr << "Failed to add name_value record\n";

	/* ===================================================== */
	// Create a NTTable pvrecord.
	
	NTTableBuilderPtr ntTableBuilder = NTTable::createBuilder();
	
	pvStructure = ntTableBuilder->
		addColumn("questions", pvString)->
		addColumn("answers", pvString)->
		addColumn("recommendations", pvString)->
		createPVStructure();
	result = master->addRecord(PVRecord::create("table", pvStructure));
	if (!result) cerr << "Failed to add table record\n";
	
	return;
}

// =============================================================
