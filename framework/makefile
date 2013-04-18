ROOT = ../
include $(ROOT)makefile.include
CFLAGS = -I$(IDIR)

all: src tests
	ar rvs $(LIBDIR)/framework.a $(ODIR)/data_manager.o $(ODIR)/simple_data_provider.o

src:
	echo 'Building Source'
	cd src/; $(MAKE) -f makefile all

tests:
	echo 'Building Tests'
	cd tests/; $(MAKE) -f makefile all

.PHONY: src tests
