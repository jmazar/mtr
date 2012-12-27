export CC = g++
export DIR  = ..
export ODIR = $(DIR)/build/obj
export BDIR = $(DIR)/build/bin
GTESTDIR = $(DIR)/3rdparty/gtest-1.6.0

framework:
	cd ../framework;
	$(MAKE) -f $(DIR)/framework/makefile

tests:
	cd $(GTESTDIR)/make/; $(MAKE) -f Makefile all
	$(MAKE) -f $(DIR)/framework/makefile tests

clean:

