#ifndef NTTEST_H
#define NTTEST_H

// ==========================================================
/*
 *	Header file for normative type test functions.
 *	
 *	These functions test the operation of the normative types:
 *		string
 *		boolean
 *		byte
 *		ubyte
 *		short
 *		ushort
 *		int
 *		uint
 *		long
 *		ulong
 *		float
 *		double
 *		
 *	There is a corresponding testArray function to each
 *	normative type.
 *
 */
// ==========================================================

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

	// Oh c++ it has been too long.
	// Do your strings need to be null terminated? 
	str[str_len + 1] = '\0';

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
		return false;
		
	return true;
}

bool testStringArray(
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "Channel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;
	
	// Write the string to the record.
	
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	// Number of strings in array is between 20 and 30
	int num_str = (rand()%10) + 20;
	
	shared_vector<string> write_str(num_str);
	
	for (int i = 0; i < num_str; ++i) 
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
	
	cout << "\n";
	for (int i = 0; i < num_str; ++i) 
	{
		cout << setw(20) << "Write string: " << data[i] << "\n";
		cout << setw(20) << "Read string: " << read_str[i] << "\n\n";

		if (data[i] != read_str[i])
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
		if (channel_name == "string")
			result = testString(pva, channel_name);	
		else if (channel_name == "stringArray")
			result = testStringArray(pva, channel_name);
		else 
		{
			cerr << "Channel name " << channel_name << " not recognized.\n";
			return false;
		}
	}
	else
	{
		cerr << "Record type " << record_type << " not recognized.\n";
		return false;
	}

	return result;
}

#endif /* NTTEST_H */
