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
	bool verbosity,
	PvaClientChannelPtr channel)
{
	bool result(true);	
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

	if(verbosity)
	{
		cout << setw(20) << "Write string: " << write_str << "\n";
		cout << setw(20) << "Read string: " << read_str << "\n\n";
	}

	if (write_str.compare(read_str) != 0)
		result = false;
		
	return result;
}

bool demoStringArray(
	bool verbosity,
	PvaClientChannelPtr channel)
{
	bool result(true);

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

		if(verbosity)
		{
			cout << setw(20) << "Write string: " << data[i] << "\n";
			cout << setw(20) << "Read string: " << read_str[i] << "\n\n";
		}

		if (data[i] != read_str[i])
			result = false;
	}
			
	return result;
}

bool demoShort(
	bool verbosity,
	PvaClientChannelPtr channel)
{
	bool result(true);

	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();

	short write = genInt(32767);
	
	putData->getPVStructure()->getSubField<PVShort>("value")->put(write);
	putGet->putGet();

	short read = getData->getPVStructure()->getSubField<PVShort>("value")->get();

	if(verbosity)
	{
		cout << setw(20) << "Write Short: " << write << "\n";
		cout << setw(20) << "Read Short: " << read << "\n\n";
	}

	if (write != read)
		result = false;

	return result;

}

bool demoShortArray(
	bool verbosity,
	PvaClientChannelPtr channel)
{
	bool result(true);

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
		if(verbosity)
		{
			cout << setw(20) << "Write Short: " << write[i] << "\n";
			cout << setw(20) << "Read Short: " << read[i] << "\n\n";
		}

		if (write[i] != read[i])
			result = false;
	}
	
	return result;
}

bool demoInt(
	bool verbosity,
	PvaClientChannelPtr channel)
{
	bool result(true);

	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();

	int write = genInt(INT_MAX);

	putData->getPVStructure()->getSubField<PVInt>("value")->put(write);
	putGet->putGet();

	int read = getData->getPVStructure()->getSubField<PVInt>("value")->get();

	if(verbosity)
	{
		cout << setw(20) << "Write Int: " << write << "\n";
		cout << setw(20) << "Read Int: " << read << "\n\n";
	}
	if (write != read)
		result = false;

	return result;

}

bool demoIntArray(
	bool verbosity,
	PvaClientChannelPtr channel)
{
	bool result(true);

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
		
		if(verbosity)
		{
			cout << setw(20) << "Write Int: " << write[i] << "\n";
			cout << setw(20) << "Read Int: " << read[i] << "\n\n";
		}

		if (write[i] != read[i])
			result = false;
	}

	return result;
}

bool demoLong(
	bool verbosity,
	PvaClientChannelPtr channel)
{
	bool result(true);

	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	PvaClientGetDataPtr getData = putGet->getGetData();

	long write = genInt(INT_MAX);

	putData->getPVStructure()->getSubField<PVLong>("value")->put(write);
	putGet->putGet();
	
	putGet->getGetData();
	
	long read = getData->getPVStructure()->getSubField<PVLong>("value")->get();
	
	if(verbosity)
	{
		cout << setw(20) << "Write Long: " << write << "\n";
		cout << setw(20) << "Read Long: " << read << "\n\n";
	}
	if (write != read)
		result = false;

	return result;
}

bool demoLongArray(
	bool verbosity,
	PvaClientChannelPtr channel)
{
	bool result(true);

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

	putGet->getGetData();
	
	// Read the data stored in the record.
	shared_vector<const long> read;
	read = getData->getPVStructure()->getSubField<PVLongArray>("value")->view();
	
	for (int i = 0; i < num; ++i) 
	{	
		if(verbosity)
		{
			cout << setw(20) << "Write Long: " << write[i] << "\n";
			cout << setw(20) << "Read Long: " << read[i] << "\n\n";
		}
		if (write[i] != read[i])
			result = false;
	}
			
	
	return result;
}

double genDouble() 
{
	double f = (double)rand() / INT_MAX;
	return f;
}

bool demoDouble(
	bool verbosity,
	PvaClientChannelPtr channel)
{
	bool result(true);

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

	if(verbosity)
	{
		cout << "\n" << setw(20) << "Write double: " << write;
		cout << "\n" << setw(20) << "Read double: " << read << "\n\n";
	}

	if (write != read)
		result = false;

	return result;
}

bool demoDoubleArray(
	bool verbosity,
	PvaClientChannelPtr channel)
{
	bool result(true);

	// Write the double to the record.
	
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	// Number of doubles in array is between 20 and 30
	int num = (rand()%10) + 20;
	
	shared_vector<double> data(num);
	
	for (int i = 0; i < num; ++i) 
		data[i] = genDouble();
	
	shared_vector<const double> write(freeze(data));
	// data is now empty

	putData->putDoubleArray(write);
	putGet->putGet();

	PvaClientGetDataPtr getData = putGet->getGetData();

	// Read the data stored in the record.
	shared_vector<const double> read;
	read = getData->getDoubleArray();
	
	for (int i = 0; i < num; ++i) 
	{

		if(verbosity)
		{
			cout << setw(20) << "Write double: " << write[i] << "\n";
			cout << setw(20) << "Read double: " << read[i] << "\n\n";
		}

		if (write[i] != read[i])
			result = false;
	}
			
	return result;
}
