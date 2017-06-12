#  ===================== ntDatabase Makefile  =====================

TOP=..

include $(TOP)/configure/CONFIG

#USR_CXXFLAGS += -std=c++0x 
ntDatabaseSRC = $(TOP)/src

# Includes
INC += pv/ntDatabase.h
INC += ntScalarDemo.h
INC += ntDemo.h

# Lib
LIBRARY += ntDatabase
LIBSRCS += ntDatabase.cpp
LIBRARY += ntDemo
LIBSRCS += ntScalarDemo.cpp ntDemo.cpp
ntDatabase_LIBS += pvaClient pvDatabase pvAccess nt pvData Com
ntDemo_LIBS +=  ntDatabase pvaClient pvDatabase pvAccess nt pvData Com

# Server
PROD_HOST += ntDatabaseMain
ntDatabaseMain_SRCS += ntDatabaseMain.cpp
ntDatabaseMain_LIBS += ntDatabase
ntDatabaseMain_LIBS += pvaClient pvDatabase pvAccess nt pvData Com

# Client
PROD_HOST += ntDatabaseClient
ntDatabaseClient_SRCS += ntDatabaseClient.cpp
ntDatabaseClient_LIBS += ntDemo 
ntDatabaseClient_LIBS += pvaClient pvAccess nt pvData ca Com

# Shared Library ABI version.
SHRLIB_VERSION ?= 1.0

include $(TOP)/configure/RULES

#  ================================================================
