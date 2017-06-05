// ============================================================= 
/*	
 *	============================================================
 *	
 *	Author: Evan Smith
 *	Date  : 6/5/2017
 * 	
 * 	ntDatabaseMain.cpp
 *
 * 	Main source file of normative type database test 
 * 	program. The programs purpose is to instantiate
 * 	and host a record containing each normative type
 * 	pv structure on a EPICS v4 database. There will be 
 *  one pvRecord for each normative type. The records'
 *  functionalities will then be tested as they will be 
 *  written to and read from over the network from a 
 *  client program (ntDatabaseClient.cpp).
 *
 *	Additional information is available in the 
 *	included README file.
 *
 *	============================================================
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <pv/channelProviderLocal.h>
#include <pv/serverContext.h>

#include <pv/ntDatabase.h>

using namespace std;

using std::tr1::static_pointer_cast;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvDatabase;
using namespace epics::ntDatabase;

int main (int argc, char **argv)
{
	
	// Get the master database maintained by the local channel provider.
	PVDatabasePtr master = PVDatabase::getMaster();
	// Get the local channel provider.
	ChannelProviderLocalPtr cpLocal = getChannelProviderLocal();

	// Create the normative type database that is defined locally in pv/ntDatabase.h
	NTDatabase::create();

	// After the records are added to the database, start the server. 
	ServerContext::shared_pointer pvaServer =
		startPVAServer("local", 0, true, true);
	
	// This was in the exampleDatabase but I think I commented it out for some reason.
	// Investigate further.
	// master.reset();

	// Wait to die.
	cout << "ntDatabase\n";
	string input;
	while (true)
	{
		cout << "Type exit to stop: \n";
		getline(cin, input);
		if (input.compare("exit") == 0) 
		{
			break;
		}
	}

	// Clean up so that we can exit cleanly.
	pvaServer->shutdown();
	pvaServer->destroy();
	cpLocal->destroy();

	return 0;
}

// ============================================================= 
