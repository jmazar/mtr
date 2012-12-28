IDIR = include/
SRC  = src/
CFLAGS = -I$(IDIR)

all: data_manager.o
	ar rvs $(BDIR)/framework.a $(ODIR)/data_manager.o

data_manager.o: $(IDIR)/IDataManager.h $(IDIR)/DataManager.h $(SRC)/DataManager.cpp
	$(CC) -c $(SRC)/DataManager.cpp -o $(ODIR)/data_manager.o $(CFLAGS)

tests:
	$(MAKE) -f $(DIR)/framework/tests/makefile
