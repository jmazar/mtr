IDIR = include/
SRC  = src/
CFLAGS = -I$(IDIR)

all: data_manager.o simple_data_provider.o
	ar rvs $(LIBDIR)/framework.a $(ODIR)/data_manager.o

data_manager.o: $(IDIR)/MtrDataModel.h $(IDIR)/IDataManager.h $(IDIR)/DataManager.h $(SRC)/DataManager.cpp
	$(CC) -c $(SRC)/DataManager.cpp -o $(ODIR)/data_manager.o $(CFLAGS)

simple_data_provider.o: $(IDIR)/MtrDataModel.h $(IDIR)/IDataProvider.h $(IDIR)/SimpleDataProvider.h $(SRC)/SimpleDataProvider.cpp
	$(CC) -c $(SRC)/SimpleDataProvider.cpp -o $(ODIR)/simple_data_provider.o $(CFLAGS)

tests:
	cd tests; $(MAKE) -f makefile all

.PHONY: tests
