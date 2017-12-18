MODULE = fir_filter

CC 		= g++
SWIG 	= swig

LDFLAGS 	= -shared
CXXFLAGS 	= -O2 -c -fpic -Wall
SWIGFLAGS 	= -c++ -python

HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

python3:   export PYTHON := python3.5
python2.7: export PYTHON := python2.7

python3: _$(MODULE).so

python2.7: _$(MODULE).so

_$(MODULE).so: %.cxx $(OBJECTS)
	@$(CC) $(LDFLAGS) $(word 2,$^)  $(MODULE)_wrap.o -o $@
	@touch __init__.py

%.cxx:
	@$(SWIG) $(SWIGFLAGS) $(MODULE).i

$(OBJECTS): $(SOURCES) $(HEADERS)
	@$(CC) -w $(CXXFLAGS) $< -o $(OBJECTS)
	@$(CC) -w $(CXXFLAGS) $(MODULE)_wrap.cxx -I/usr/include/$(PYTHON)

clean:
	@rm -f *.o *wrap* *.out *.py *.so *.pyc
