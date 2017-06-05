#ifndef NTDATABASE_H
#define NTDATABASE_H

#ifdef epicsExportSharedSymbols
#	define  ntDatabaseEpicsExportSharedSymbols
#	undef   epicsExportSharedSymbols
#endif

#include <pv/pvDatabase.h>

#ifdef ntDatabaseEpicsExportSharedSymbols
#	define epicsExportSharedSymbols  
#	undef  ntDatabaseEpicsExportSharedSymbols
#endif

#include <shareLib.h>

namespace epics { namespace ntDatabase {

	class epicsShareClass NTDatabase {
		public:
			static void create();
	};
	
}}


#endif /* NTDATABASE_H */
