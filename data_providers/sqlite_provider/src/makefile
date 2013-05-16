ROOT = ../../../
FRAMEWORKDIR = $(ROOT)framework/$(IDIR)
SQLITEDIR = $(ROOT)3rdparty/sqlite
include $(ROOT)makefile.include
CFLAGS = -I../$(IDIR) -I$(FRAMEWORKDIR) -I$(SQLITEDIR)

all: sqlite.o sqlite_data_provider.o
	ar rvs $(ROOT)$(LIBDIR)sqlite_data_provider.a $(ROOT)$(ODIR)sqlite_data_provider.o $(ROOT)$(ODIR)sqlite.o

sqlite_data_provider.o: $(FRAMEWORKDIR)MtrDataModel.h $(FRAMEWORKDIR)IDataProvider.h ../$(IDIR)sqlite_data_provider.h sqlite_data_provider.cpp
	$(CC) -c sqlite_data_provider.cpp -o $(ROOT)$(ODIR)sqlite_data_provider.o $(CFLAGS)

sqlite.o: $(SQLITEDIR)/sqlite3.h $(SQLITEDIR)/sqlite3.c
	gcc -c $(SQLITEDIR)/sqlite3.c -o $(ROOT)$(ODIR)sqlite.o
