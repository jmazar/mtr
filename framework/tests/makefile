SRC = ./
IDIR = ../include
GTESTDIR = ../../3rdparty/gtest-1.6.0
GTESTINCLUDEDIR = $(GTESTDIR)/include
GTESTLIBDIR =  $(GTESTDIR)/make

CFLAGS = -I$(IDIR) -I$(GTESTINCLUDEDIR)

all: data_manager_unit_test.o
	$(CC) -o ../$(BDIR)/DataManagerUnitTest ../$(ODIR)/data_manager_unit_test.o ../$(LIBDIR)/framework.a $(GTESTLIBDIR)/gtest_main.a
data_manager_unit_test.o:
	$(CC) -c $(SRC)DataManagerUnitTest.cpp  -o ../$(ODIR)/data_manager_unit_test.o $(CFLAGS)

