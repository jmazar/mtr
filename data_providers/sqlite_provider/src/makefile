ROOT = ../../../
FRAMEWORKDIR = $(ROOT)framework/$(IDIR)
include $(ROOT)makefile.include
CFLAGS = -I../$(IDIR) -I$(FRAMEWORKDIR)

all: sqlite_data_provider.o
	#ar rvs $(ROOT)$(LIBDIR)framework.a $(ROOT)$(ODIR)data_manager.o $(ROOT)$(ODIR)simple_data_provider.o

sqlite_data_provider.o: $(FRAMEWORKDIR)MtrDataModel.h $(FRAMEWORKDIR)IDataProvider.h ../$(IDIR)sqlite_data_provider.h sqlite_data_provider.cpp
	$(CC) -c sqlite_data_provider.cpp -o $(ROOT)$(ODIR)sqlite_data_provider.o $(CFLAGS)

