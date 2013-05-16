include ../../makefile.include
CFLAGS = -I$(IDIR)

all: src test
	#ar rvs $(LIBDIR)framework.a $(ODIR)data_manager.o $(ODIR)simple_data_provider.o

src:
	cd src; $(MAKE) -f makefile all

test:
	cd test; $(MAKE) -f makefile all

.PHONY: src test
