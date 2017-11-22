MODULE = fir_filter

CC 		= g++
SWIG 	= swig

LDFLAGS 	= -shared
CXXFLAGS 	= -O2 -c -fpic -Wall
SWIGFLAGS 	= -c++ -python

HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

_$(MODULE).so: %.cxx $(OBJECTS)
	@$(CC) $(LDFLAGS) $(word 2,$^)  $(MODULE)_wrap.o -o $@
	@touch __init__.py

%.cxx:
	@$(SWIG) $(SWIGFLAGS) $(MODULE).i

$(OBJECTS): $(SOURCES) $(HEADERS)
	@$(CC) -w $(CXXFLAGS) $< -o $(OBJECTS)
	@$(CC) -w $(CXXFLAGS) $(MODULE)_wrap.cxx -I/usr/include/python2.7

clean:
	@rm -f *.o *wrap* *.out *.py *.so *.pyc
