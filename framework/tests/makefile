ROOT = ../../
include $(ROOT)makefile.include
GTESTDIR = $(ROOT)3rdparty/gtest-1.6.0/
GTESTIDIR = $(GTESTDIR)$(IDIR)
GTESTLIBDIR =  $(GTESTDIR)make/

CFLAGS = -I../$(IDIR) -I$(GTESTIDIR)

all: data_manager_unit_test.o
	$(CC) -o $(ROOT)$(BDIR)DataManagerUnitTest $(ROOT)$(ODIR)data_manager_unit_test.o $(ROOT)$(LIBDIR)framework.a $(GTESTLIBDIR)gtest_main.a -pthread

data_manager_unit_test.o:
	$(CC) -c DataManagerUnitTest.cpp  -o $(ROOT)$(ODIR)data_manager_unit_test.o $(CFLAGS)

