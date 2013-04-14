ROOT = ../../../
include $(ROOT)makefile.include
SQLITEDIR = $(ROOT)3rdparty/sqlite
FRAMEWORKDIR = $(ROOT)framework/$(IDIR)
GTESTDIR = $(ROOT)3rdparty/gtest-1.6.0/
GTESTIDIR = $(GTESTDIR)$(IDIR)
GTESTLIBDIR =  $(GTESTDIR)make/

CFLAGS = -I../$(IDIR) -I$(GTESTIDIR) -I$(FRAMEWORKDIR)

all: sqlite_data_provider_gtest.o
	$(CC) -o $(ROOT)$(BDIR)sqlite_data_provider_gtest $(ROOT)$(ODIR)sqlite_data_provider_gtest.o $(ROOT)$(LIBDIR)sqlite_data_provider.a $(ROOT)$(LIBDIR)framework.a $(GTESTLIBDIR)gtest_main.a -pthread -ldl

sqlite_data_provider_gtest.o:
	$(CC) -c sqlite_data_provider_gtest.cpp  -o $(ROOT)$(ODIR)sqlite_data_provider_gtest.o $(CFLAGS)
