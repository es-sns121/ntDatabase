template < typename SCALAR_TYPE > 
bool demoScalar(
	bool verbosity,
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

	read = getData->getPVStructure()->getSubField<PVScalarValue<SCALAR_TYPE>>("value")->get();

	if(verbosity)
	{
		cout << "\n" << setw(20) << "Write value: " << write;
		cout << "\n" << setw(20) << "Read value: " << read << "\n\n";
	}

	if (write != read)
		return false;
	
	return (true && demoDoubleArray<SCALAR_TYPE>(verbosity, pva, string(channel_name + "Array")));
}

template < typename SCALAR_TYPE > 
bool demoScalarArray(
	bool verbosity,
	PvaClientPtr const &pva,
	string const &channel_name)
{
	PvaClientChannelPtr channel = pva->channel(channel_name);
	
	if (channel) cout << "\nChannel \"" << channel_name << "\" connected succesfully\n";
	else
		return false;
	
	// Write the double to the record.
	
	PvaClientPutGetPtr putGet = channel->createPutGet("");
	PvaClientPutDataPtr putData = putGet->getPutData();
	// Number of doubles in array is between 20 and 30
	int num = (rand()%10) + 20;
	
	shared_vector<SCALAR_TYPE> data(num);
	
	for (int i = 0; i < num; ++i) 
		data[i] = genDouble();
	
	shared_vector<const SCALAR_TYPE> write(freeze(data));
	// data is now empty

	putData->putDoubleArray(write);
	putGet->putGet();

	PvaClientGetDataPtr getData = putGet->getGetData();

	// Read the data stored in the record.
	shared_vector<const SCALAR_TYPE> read;
	read = getData->getPVStructure()->getSubField<PVScalarValue<SCALAR_TYPE>>("value")->view();
	
	for (int i = 0; i < num; ++i) 
	{

		if(verbosity)
		{
			cout << setw(20) << "Write value: " << write[i] << "\n";
			cout << setw(20) << "Read value: " << read[i] << "\n\n";
		}

		if (write[i] != read[i])
			return false;
	}
			
	return true;
}
