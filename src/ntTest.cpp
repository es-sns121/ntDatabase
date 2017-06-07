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

	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();
	
	PVStructurePtr pvStructure = putData->getPVStructure();
	shared_vector<const string> choices = pvStructure->getSubField<PVStringArray>("value.choices")->view();
	int read = pvStructure->getSubField<PVInt>("value.index")->get();
	
	if (verbosity)
	{
		cout << "\n\tBefore write: enum(one, zero) = " << choices[read] << endl;
	}
	
	int write = 1;
	pvStructure->getSubField<PVInt>("value.index")->put(write);

	putGet->putGet();

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
