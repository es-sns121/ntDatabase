/* 
 * ==========================================================
 *	
 *	ntDemo.cpp
 *
 *	normative type demo source file.
 *	
 *	warning: this code is kind of clunky.
 *	read at your own risk.
 *
 * ==========================================================
 */

#include "ntScalarDemo.h"

bool verbosity_flag;

// Crappy method of generating a random integer.
long genInt(long high) {
	return rand() % high;
}

string genString() {
	
	// Generate pseudo random alphanumeric input to be written to record.
	
	// String size between 10 and 50
	size_t str_len = (rand() % 41) + 10;
	
	string str;
	str.resize(str_len + 1);
	
	for (size_t i = 0; i < str_len; ++i) {
		// ascii characters 33 -> 126 are printable
		// not including space which is 32.
		str[i] = (rand()%94) + 33;
	}

	return str;
}

bool demoString(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
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

	if(verbosity_flag)
	{
		cout << setw(20) << "Write string: " << write_str << "\n";
		cout << setw(20) << "Read string: " << read_str << "\n\n";
	}

	if (write_str.compare(read_str) != 0)
		return false;
		
	return true;
}

bool demoStringArray(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;
	
	// Write the string to the record.
	
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	// Number of strings in array is between 20 and 30
	int numstr = (rand()%10) + 20;
	
	shared_vector<string> write_str(numstr);
	
	for (int i = 0; i < numstr; ++i) 
		write_str[i] = genString();
	
	// NOTE: when freeze is executed, all data from write_str is removed.
	shared_vector<const string> data(freeze(write_str));
	// write_str is now empty.
	
	putData->putStringArray(data);
	putGet->putGet();

	PvaClientGetDataPtr getData = putGet->getGetData();

	// Read the data stored in the record.
	shared_vector<const string> read_str;
	read_str = getData->getStringArray();
	
	for (int i = 0; i < numstr; ++i) 
	{

		if(verbosity_flag)
		{
			cout << setw(20) << "Write string: " << data[i] << "\n";
			cout << setw(20) << "Read string: " << read_str[i] << "\n\n";
		}

		if (data[i] != read_str[i])
			return false;
	}
			
	return true;
}

bool demoShort(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;

	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();

	bool result(false);

	short write = genInt(32767);

	putData->getPVStructure()->getSubField<PVShort>("value")->put(write);
	putGet->putGet();

	short read = getData->getPVStructure()->getSubField<PVShort>("value")->get();

	if(verbosity_flag)
	{
		cout << setw(20) << "Write Short: " << write << "\n";
		cout << setw(20) << "Read Short: " << read << "\n\n";
	}

	if (write == read)
		result = true;

	return result;

}

bool demoShortArray(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;
	
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();
	
	// Number of ints in array is between 20 and 30
	int num = (rand()%10) + 20;
	
	shared_vector<short> data(num);
	
	for (int i = 0; i < num; ++i) 
		data[i] = genInt(32767);
	
	shared_vector<const short> write(freeze(data));
	// the data vector is now empty.
	
	putData->getPVStructure()->getSubField<PVShortArray>("value")->replace(write);
	putGet->putGet();

	// Read the data stored in the record.
	shared_vector<const short> read;
	read = getData->getPVStructure()->getSubField<PVShortArray>("value")->view();
	
	for (int i = 0; i < num; ++i) 
	{
		if(verbosity_flag)
		{
			cout << setw(20) << "Write Short: " << write[i] << "\n";
			cout << setw(20) << "Read Short: " << read[i] << "\n\n";
		}

		if (write[i] != read[i])
			return false;
	}
			
	return true;
}

bool demoInt(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;

	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();

	bool result(false);

	int write = genInt(INT_MAX);

	putData->getPVStructure()->getSubField<PVInt>("value")->put(write);
	putGet->putGet();

	int read = getData->getPVStructure()->getSubField<PVInt>("value")->get();

	if(verbosity_flag)
	{
		cout << setw(20) << "Write Int: " << write << "\n";
		cout << setw(20) << "Read Int: " << read << "\n\n";
	}
	if (write == read)
		result = true;

	return result;

}

bool demoIntArray(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);

	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;
	
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();
	
	// Number of ints in array is between 20 and 30
	int num = (rand()%10) + 20;
	
	shared_vector<int> data(num);
	
	for (int i = 0; i < num; ++i) 
		data[i] = genInt(INT_MAX);
	
	shared_vector<const int> write(freeze(data));
	// the data vector is now empty.
	
	putData->getPVStructure()->getSubField<PVIntArray>("value")->replace(write);
	putGet->putGet();

	// Read the data stored in the record.
	shared_vector<const int> read;
	read = getData->getPVStructure()->getSubField<PVIntArray>("value")->view();
	
	for (int i = 0; i < num; ++i) 
	{
		
		if(verbosity_flag)
		{
			cout << setw(20) << "Write Int: " << write[i] << "\n";
			cout << setw(20) << "Read Int: " << read[i] << "\n\n";
		}

		if (write[i] != read[i])
			return false;
	}
			
	return true;
}

bool demoLong(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;


	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();

	bool result(false);

	long write = genInt(INT_MAX);

	putData->getPVStructure()->getSubField<PVLong>("value")->put(write);
	putGet->putGet();

	long read = getData->getPVStructure()->getSubField<PVLong>("value")->get();
	
	if(verbosity_flag)
	{
		cout << setw(20) << "Write Long: " << write << "\n";
		cout << setw(20) << "Read Long: " << read << "\n\n";
	}
	if (write == read)
		result = true;

	return result;

}

bool demoLongArray(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;
	
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();
	
	// Number of longs in array is between 20 and 30
	int num = (rand()%10) + 20;
	
	shared_vector<long> data(num);
	
	for (int i = 0; i < num; ++i) 
		data[i] = genInt(INT_MAX);
	
	shared_vector<const long> write(freeze(data));
	// the data vector is now empty.
	
	putData->getPVStructure()->getSubField<PVLongArray>("value")->replace(write);
	putGet->putGet();

	// Read the data stored in the record.
	shared_vector<const long> read;
	read = getData->getPVStructure()->getSubField<PVLongArray>("value")->view();
	
	for (int i = 0; i < num; ++i) 
	{	
		if(verbosity_flag)
		{
			cout << setw(20) << "Write Long: " << write[i] << "\n";
			cout << setw(20) << "Read Long: " << read[i] << "\n\n";
		}
		if (write[i] != read[i])
			return false;
	}
			
	return true;
}

double genDouble() 
{
	double f = (double)rand() / INT_MAX;
	return f;
}

bool demoDouble(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;
	
	double write = genDouble();

	// Write the string to the record.
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	
	putData->putDouble(write);
	putGet->putGet();

	// Read the data stored in the record.
	double read;
	
	PvaClientGetDataPtr getData = putGet->getGetData();

	read = getData->getDouble();

	if(verbosity_flag)
	{
		cout << "\n" << setw(20) << "Write double: " << write << "\n";
		cout << setw(20) << "Read double: " << read << "\n\n";
	}

	if (write != read)
		return false;
		
	return true;
}

bool demoDoubleArray(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;
	
	// Write the string to the record.
	
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	// Number of strings in array is between 20 and 30
	int num = (rand()%10) + 20;
	
	shared_vector<double> data(num);
	
	for (int i = 0; i < num; ++i) 
		data[i] = genDouble();
	
	// NOTE: when freeze is executed, all data from write_str is removed.
	shared_vector<const double> write(freeze(data));
	// write_str is now empty.
	
	putData->putDoubleArray(write);
	putGet->putGet();

	PvaClientGetDataPtr getData = putGet->getGetData();

	// Read the data stored in the record.
	shared_vector<const double> read;
	read = getData->getDoubleArray();
	
	for (int i = 0; i < num; ++i) 
	{

		if(verbosity_flag)
		{
			cout << setw(20) << "Write double: " << write[i] << "\n";
			cout << setw(20) << "Read double: " << read[i] << "\n\n";
		}

		if (write[i] != read[i])
			return false;
	}
			
	return true;
}

// This is hideous. Creating a map of recordType/demoFunction key value pairs, and then
// just searching for the function would be better.
// Parse the record request and call the respective function.
bool demoScalarRecord(
	bool const &verbosity,
	PvaClientPtr const &pva,
	string const &channel_name,
	string const &record_type)
{
	verbosity_flag = verbosity;

	bool result(false);
	if (record_type == "string") {
		if (channel_name == "string")
			result = demoString(pva, channel_name);	
		else if (channel_name == "stringArray")
			result = demoStringArray(pva, channel_name);
		else {
			cerr << "Channel name " << channel_name << " not recognized.\n";
			return false;
		}
	} else if (record_type == "short") {
		if (channel_name == "short")
			result = demoShort(pva, channel_name);	
		else if (channel_name == "shortArray")
			result = demoShortArray(pva, channel_name);
		else {
			cerr << "Channel name " << channel_name << " not recognized.\n";
			return false;
		}		
	} else if (record_type == "int") {
		if (channel_name == "int")
			result = demoInt(pva, channel_name);	
		else if (channel_name == "intArray")
			result = demoIntArray(pva, channel_name);
		else {
			cerr << "Channel name " << channel_name << " not recognized.\n";
			return false;
		}
	} else if (record_type == "long") {
		if (channel_name == "long")
			result = demoLong(pva, channel_name);	
		else if (channel_name == "longArray")
			result = demoLongArray(pva, channel_name);
		else {
			cerr << "Channel name " << channel_name << " not recognized.\n";
			return false;
		}	
	} else if (record_type == "double") {
		if (channel_name == "double")
			result = demoDouble(pva, channel_name);	
		else if (channel_name == "doubleArray")
			result = demoDoubleArray(pva, channel_name);
		else {
			cerr << "Channel name " << channel_name << " not recognized.\n";
			return false;
		}		
	} else {
		cerr << "Record type " << record_type << " not recognized.\n";
		return false;
	}

	return result;
}

