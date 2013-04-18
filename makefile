ROOT = ./
include $(ROOT)makefile.include
GTESTDIR = 3rdparty/gtest-1.6.0

all: framework tests

framework:
	echo 'Building Framework'
	cd framework; $(MAKE) -f makefile

tests: framework
	ehcho 'Building Tests'
	cd $(GTESTDIR)/make/; $(MAKE) -f Makefile all
	cd $(DIR)/framework/; $(MAKE) -f makefile tests

clean:
	rm -rf $(ODIR)/*
	rm -rf $(BDIR)/*
	rm -rf $(LIBDIR)/*
	cd $(GTESTDIR)/make/; $(MAKE) -f Makefile clean

.PHONY: framework tests clean
