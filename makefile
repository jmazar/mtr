ROOT = ./
include $(ROOT)makefile.include
GTESTDIR = 3rdparty/gtest-1.6.0

all: framework tests

framework:
	cd framework; $(MAKE) -f framework/makefile

tests: framework
	cd $(GTESTDIR)/make/; $(MAKE) -f Makefile all
	cd $(DIR)/framework/; $(MAKE) -f makefile tests

clean:
	rm -rf $(ODIR)/*
	rm -rf $(BDIR)/*
	rm -rf $(LIBDIR)/*
	cd $(GTESTDIR)/make/; $(MAKE) -f Makefile clean

.PHONY: framework tests clean
