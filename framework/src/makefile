ROOT = ../../
include $(ROOT)makefile.include
CFLAGS = -I../$(IDIR)

all: data_manager.o simple_data_provider.o

data_manager.o: ../$(IDIR)MtrDataModel.h ../$(IDIR)IDataManager.h ../$(IDIR)DataManager.h DataManager.cpp
	$(CC) -c DataManager.cpp -o $(ROOT)$(ODIR)data_manager.o $(CFLAGS)

simple_data_provider.o: ../$(IDIR)MtrDataModel.h ../$(IDIR)IDataProvider.h ../$(IDIR)SimpleDataProvider.h SimpleDataProvider.cpp
	$(CC) -c SimpleDataProvider.cpp -o $(ROOT)$(ODIR)simple_data_provider.o $(CFLAGS)

