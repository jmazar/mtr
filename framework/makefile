IDIR = $(DIR)framework/include
SRC  = $(DIR)framework/src

all: data_manager.o
	ar rvs $(BDIR)/framework.a $(ODIR)/data_manager.o

data_manager.o: $(IDIR)/IDataManager.h $(IDIR)/DataManager.h $(SRC)/DataManager.cpp
	$(CC) -c $(SRC)/DataManager.cpp -o $(ODIR)/data_manager.o 

tests:
	$(MAKE) tests/makefile
