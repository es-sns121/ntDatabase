// =======================================================================
/*
 * =======================================================================
 * 
 * 	Author: Evan Smith
 * 	Date  : 6/5/2017
 *
 * 	ntDatabaseClient.cpp
 *
 * 	Source file for client side of normative type database test program.
 *
 * =======================================================================
 */

#include <iomanip>
#include <iostream>
#include <memory>
#include <time.h>
#include <vector>


#include <pv/pvaClient.h>
#include <pv/pvData.h>
#include <pv/pvAccess.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvaClient;

string genString() {
	
	// Generate pseudo random alphanumeric input to be written to record.
	size_t str_len = (rand() % 41) + 10;
	
	string str;
	str.resize(str_len);
	
	for (size_t i = 0; i < str_len; ++i) {
		// ascii characters 33 -> 126 are printable
		// not including space which is 32.
		str[i] = (rand()%94) + 33;
	}

	return str;
}

bool testString(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "Channel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;
	
	string write_str = genString();

	// Write the string to the record.
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();

	putData->putString(write_str);
	putGet->putGet();

	// Read the data stored in the record.
	string read_str;
	
	PvaClientGetDataPtr getData = putGet->getGetData();

	read_str = getData->getString();

	cout << "\n" << setw(20) << "Write string: " << write_str << "\n";
	cout << setw(20) << "Read string: " << read_str << "\n\n";

	if (write_str.compare(read_str) != 0)
	{
		return false;
	}
		
	return true;
}

bool testRecord(
	PvaClientPtr const &pva,
	string const &channel_name,
	string const &record_type)
{
	bool result(false);
	if (record_type == "string") 
	{
		// call testString function
		result = testString(pva, channel_name);	
	}
	else
	{
		cerr << "Record type " << record_type << " not recognized.\n";
		return false;
	}

	return result;
}

int main (int argc, char **argv)
{
	cout << "ntDatabase Client\n";
	
	try {
	
		PvaClientPtr pvaClient = PvaClient::get("pva");
		// add debug option
	
		srand(time(NULL));

		bool result;
		// Basic string test. 
		result = testRecord(pvaClient, "string01", "string");
		if (result)
		{
			cout << "Record test successful\n";
		}
		else 
		{
			cout << "Record test unsuccessful\n";
		}

	} catch (std::runtime_error e) {
		
		cerr << "exception: " << e.what() << endl;
		return -1;
	
	}

	return 0;
}

// =======================================================================
