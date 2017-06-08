#include "ntTest.h"
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
	string const & channel_name)
{
	bool result(false);
	
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return result;

	// Create putGet to read and write to/from record.
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();
	
	PVStructurePtr pvStructure = putData->getPVStructure();
	// Request copy of the choices array in the enum
	shared_vector<const string> choices = pvStructure->getSubField<PVStringArray>("value.choices")->view();
	// Get current index of choices array in the enum
	int read = pvStructure->getSubField<PVInt>("value.index")->get();
	
	if (verbosity)
	{
		cout << "\n\tBefore write: enum(one, zero) = " << choices[read] << endl;
	}
	
	// Write a new index to the record.
	int write = 1;
	pvStructure->getSubField<PVInt>("value.index")->put(write);

	putGet->putGet();

	// Check that it changed.
	pvStructure = getData->getPVStructure();
	read = pvStructure->getSubField<PVInt>("value.index")->get();

	if (verbosity)
	{
		cout << "\tAfter write: enum(one, zero) = " << choices[read] << endl << endl;
	}

	if (read == write)
		result = true;

	return result;
}

bool testMatrix(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name)
{
	bool result(true);
	
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return result;

	// Create putGet to read and write to/from record.
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();
	
	// Dimensions of matrix, 2 x 2 for a total of 4 cells.
	shared_vector<int> dim_data(2);
	dim_data[0] = 5; dim_data[1] = 5;
	
	// Values to be inserted into matrix.
	shared_vector<double> val_data(25);
	for (int i = 0; i < 25; ++i) val_data[i] = (double) i;
	
	shared_vector<const int> dim(freeze(dim_data));
	shared_vector<const double> value(freeze(val_data));
	// Note that the data vectors are now empty.
	
	// Replace the data in the record's vectors and flush the changed bitsets to the server.
	putData->getPVStructure()->getSubField<PVIntArray>("dim")->replace(dim);	
	putData->getPVStructure()->getSubField<PVDoubleArray>("value")->replace(value);	
	putGet->putGet();

	// Read the data from the record and check that it is correct.
	shared_vector<const int> read_dim;
	shared_vector<const double> read_val;

	putGet->getGetData();
	read_dim = getData->getPVStructure()->getSubField<PVIntArray>("dim")->view();
	read_val = getData->getPVStructure()->getSubField<PVDoubleArray>("value")->view();

	stringstream out;
	out << "\n\tMatrix: ";
	out << "dim:";
	for (size_t i = 0; i < read_dim.size(); ++i) {
		out << " " << read_dim[i];
		if (read_dim[i] != dim[i])
			result = false;
	}
	
	out << "\n\t        val:";
	for (size_t i = 0, j = 0; i < read_val.size() && j < read_dim.size(); ++i) { 
		out << " " << read_val[i];
		if (read_val[i] != value[i])
			result = false;
	}
	out << "\n\n";

	if (verbosity)
		cout << out.str();

	return result;
}


bool testURI(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name)
{
	bool result(false);
	
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return result;

	// Create putGet to read and write to/from record.
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();
	
	string scheme_write = "URI scheme string";
	string path_write = "URI path string";
	string query_write = "URI query string";
	
	// Write data to the record.
	putData->getPVStructure()->getSubField<PVString>("scheme")->put(scheme_write);
	putData->getPVStructure()->getSubField<PVString>("path")->put(path_write);
	putData->getPVStructure()->getSubField<PVString>("query.query")->put(query_write);
	putGet->putGet();

	string scheme_read;
	string path_read;
	string query_read;

	putGet->getGetData();	
	scheme_read = getData->getPVStructure()->getSubField<PVString>("scheme")->get();
	path_read = getData->getPVStructure()->getSubField<PVString>("path")->get();
	query_read = getData->getPVStructure()->getSubField<PVString>("query.query")->get();
	
	stringstream out;
	out << "\n\twrite\n";
	out << "\t\t" << setw(8) << "scheme: " << scheme_write << endl;
	out << "\t\t" << setw(8) << "path: " << path_write << endl;
	out << "\t\t" << setw(8) << "query: " << query_write << endl;
	

	out << "\tread\n";
	out << "\t\t" << setw(8) << "scheme: " << scheme_read << endl;
	out << "\t\t" << setw(8) << "path: " << path_read << endl;
	out << "\t\t" << setw(8) << "query: " << query_read << endl << endl;

	if (scheme_write == scheme_read &&
		path_write == path_read &&
		query_write == query_read)
		result = true;

	if (verbosity)
		cout << out.str();

	return result;
}

bool testNameValue(
	bool verbosity,
	PvaClientPtr const & pva,
	string const & channel_name)
{
	bool result(true);
	
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return result;

	// Create putGet to read and write to/from record.
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();
	
	// Create a vector of names for the record.
	shared_vector<string> name_data;
	name_data.push_back("one");
	name_data.push_back("two");
	name_data.push_back("three");
	shared_vector<const string> name(freeze(name_data));
	
	// Create a vector of values for the record.
	shared_vector<double> value_data;
	value_data.push_back(1);
	value_data.push_back(2);
	value_data.push_back(3);
	shared_vector<const double> value(freeze(value_data));
	
	// Write the names and values to the record.
	putData->getPVStructure()->getSubField<PVStringArray>("name")->replace(name);
	putData->getPVStructure()->getSubField<PVDoubleArray>("value")->replace(value);
	putGet->putGet();

	// Read the names and values from the record.
	putGet->getGetData();
	shared_vector<const string> name_read = getData->getPVStructure()->getSubField<PVStringArray>("name")->view();
	shared_vector<const double> value_read = getData->getPVStructure()->getSubField<PVDoubleArray>("value")->view();
	
	stringstream out;
	out << "\n\t names:";
	for(size_t i = 0; i < name_read.size(); ++i) {
		out << right << setw(8) << name_read[i];
		if (name[i] != name_read[i])
			result = false;
	}
	out << "\n\tvalues:";
	for(size_t i = 0; i < value_read.size(); ++i) {
		out << setw(8) << value_read[i];
		if (value[i] != value_read[i])
			result = false;
	}
	out << "\n\n";
	
	if (verbosity)
		cout << out.str();

	return result;
}


// ========================================== BOTTOM ========================================== //
