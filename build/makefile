export CC = g++
export DIR  = ..
export ODIR = $(DIR)/build/obj
export BDIR = $(DIR)/build/bin
export LIBDIR = $(DIR)/build/lib
GTESTDIR = $(DIR)/3rdparty/gtest-1.6.0

framework:
	cd ../framework; $(MAKE) -f $(DIR)/framework/makefile

tests: framework
	cd $(GTESTDIR)/make/; $(MAKE) -f Makefile all
	cd $(DIR)/framework/; $(MAKE) -f makefile tests

clean:
	rm -rf $(ODIR)/*
	rm -rf $(BDIR)/*
	rm -rf $(LIBDIR)/*

.PHONY: tests

