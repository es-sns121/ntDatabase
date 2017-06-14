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
#include <pv/ntattribute.h>
#include <pv/ntmultiChannel.h>
#include <pv/ntndarray.h>
#include <pv/ntcontinuum.h>
#include <pv/nthistogram.h>
#include <pv/ntaggregate.h>

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
static void createScalarRecords(
	PVDatabasePtr const &master,
	ScalarType scalarType,
	string const &recordNamePrefix)
{
	string recordName = recordNamePrefix;
	
	NTScalarBuilderPtr ntScalarBuilder = NTScalar::createBuilder();
	
	// Create the pvStructure to be inserted into the record.
	PVStructurePtr pvStructure = ntScalarBuilder->
		value(scalarType)->
		addAlarm()->
		addTimeStamp()->
		createPVStructure();

	// Create the record and attempt to add it to the database.	
	PVRecordPtr pvRecord = PVRecord::create(recordName, pvStructure);
	
	bool result = master->addRecord(pvRecord);
	if (!result) cerr << "Failed to add record " << recordName << " to database\n";

	recordName += "Array";
	
	// Create the pvStructure for the array type to be inserted into the record.
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
	
	// Create string and string array records.	
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
	// Create the choices vector for the enum.
	shared_vector<string> choices(2);
	choices[0] = "zero";
	choices[1] = "one";
	// Get the structure's array and replace it with the newly created vector.
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
	
	/* ===================================================== */
	// Create a NTAttribute pvrecord.
	
	NTAttributeBuilderPtr ntAttributeBuilder = NTAttribute::createBuilder();
	
	pvStructure = ntAttributeBuilder->
		createPVStructure();
	result = master->addRecord(PVRecord::create("attribute", pvStructure));
	if (!result) cerr << "Failed to add attribute record\n";
	
	/* ===================================================== */
	// Create a NTMultiChannel pvrecord.
	
	NTMultiChannelBuilderPtr ntMultiChannelBuilder = NTMultiChannel::createBuilder();
	
	pvStructure = ntMultiChannelBuilder->
		addIsConnected()->
		createPVStructure();
	result = master->addRecord(PVRecord::create("multi_channel", pvStructure));
	if (!result) cerr << "Failed to add multi_channel record\n";
	
	/* ===================================================== */
	// Create a NTNDArray pvrecord.
	
	NTNDArrayBuilderPtr ntNDArrayBuilder = NTNDArray::createBuilder();
	
	pvStructure = ntNDArrayBuilder->
		createPVStructure();
	result = master->addRecord(PVRecord::create("ndarray", pvStructure));
	if (!result) cerr << "Failed to add ndarray record\n";
	
	/* ===================================================== */
	// Create a NTContinuum pvrecord.
	
	NTContinuumBuilderPtr ntContinuumBuilder = NTContinuum::createBuilder();
	
	pvStructure = ntContinuumBuilder->
		createPVStructure();
	result = master->addRecord(PVRecord::create("continuum", pvStructure));
	if (!result) cerr << "Failed to add continuum record\n";
	
	/* ===================================================== */
	// Create a NTHistogram pvrecord.
	
	NTHistogramBuilderPtr ntHistogramBuilder = NTHistogram::createBuilder();
	
	pvStructure = ntHistogramBuilder->
		value(pvLong)->
		createPVStructure();
	result = master->addRecord(PVRecord::create("histogram", pvStructure));
	if (!result) cerr << "Failed to add histogram record\n";
	
	/* ===================================================== */
	// Create a NTAggregate pvrecord.
	
	NTAggregateBuilderPtr ntAggregateBuilder = NTAggregate::createBuilder();
	
	pvStructure = ntAggregateBuilder->
		createPVStructure();
	result = master->addRecord(PVRecord::create("aggregate", pvStructure));
	if (!result) cerr << "Failed to add aggregate record\n";
	
	return;
}

