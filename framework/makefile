include ../makefile.include
CFLAGS = -I$(IDIR)

all: src tests
	ar rvs $(LIBDIR)/framework.a $(ODIR)/data_manager.o $(ODIR)/simple_data_provider.o

src:
	$(MAKE) -f src/makefile all

tests:
	$(MAKE) -f tests/makefile all

.PHONY: src tests
