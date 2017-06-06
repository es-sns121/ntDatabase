#  ===================== ntDatabase Makefile  =====================

TOP=..

include $(TOP)/configure/CONFIG

ntDatabaseSRC = $(TOP)/src

# Includes
INC += pv/ntDatabase.h
INC += ntTest.h

# Lib
LIBRARY += ntDatabase
LIBSRCS += ntDatabase.cpp
LIBRARY += ntTest
LIBSRCS += ntTest.cpp
ntDatabase_LIBS += pvaClient pvDatabase pvAccess nt pvData Com
ntTest_LIBS +=  ntDatabase pvaClient pvDatabase pvAccess nt pvData Com

# Server
PROD_HOST += ntDatabaseMain
ntDatabaseMain_SRCS += ntDatabaseMain.cpp
ntDatabaseMain_LIBS += ntDatabase
ntDatabaseMain_LIBS += pvaClient pvDatabase pvAccess nt pvData Com

# Client
PROD_HOST += ntDatabaseClient
ntDatabaseClient_SRCS += ntDatabaseClient.cpp
ntDatabaseClient_LIBS += ntTest 
ntDatabaseClient_LIBS += pvaClient pvAccess nt pvData ca Com

# Shared Library ABI version.
SHRLIB_VERSION ?= 1.0

include $(TOP)/configure/RULES

#  ================================================================
