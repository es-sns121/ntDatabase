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
	bool result(false);
	
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return result;

	// Create putGet to read and write to/from record.
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();
	
	// Dimensions of matrix, 2 x 2 for a total of 4 cells.
	shared_vector<int> data1(2);
	data1[0] = 2; data1[1] = 2;
	
	// Data to be inserted into matrix.
	shared_vector<double> data2(4);
	for (int i = 0; i < 4; ++i) data2[i] = (double) i;
	
	shared_vector<const int> dim(freeze(data1));
	shared_vector<const double> value(freeze(data2));
	// Note that the data vectors are now empty.
	
	putData->getPVStructure()->getSubField<PVIntArray>("dim")->replace(dim);	
	putData->getPVStructure()->getSubField<PVDoubleArray>("value")->replace(value);	
	putGet->putGet();

	return result;
}



