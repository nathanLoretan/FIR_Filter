# FIR_Filter
This reposite implements a FIR filter designing for lowpass, highpass, bandpass, bandstop. It is designed in C++. However, it is possible to use this FIR filter as a python module. Therefore, the open-source software SWIG is used to convert C/C++ language in script language as Python or Java. The code, a demo and an howto can be found on \url{https://www.github.com/nathanLoretan/FIR_Filter}.

To ease the compilation of the C++ class, a simple Makefile is created.
  >>> cd /path/to/FIR_filter
  >>> make

The makefile compiles the C++ class and create the python module. Then the python package can be simply improted in a script.
  >>> from F  IR_filter.fir_filter import FIR_filter

