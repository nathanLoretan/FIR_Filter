# FIR_Filter
This reposite implements a FIR filter designing for lowpass, highpass, bandpass,
bandstop. It is designed in C++. However, it is possible to use this FIR filter
as a python module. Therefore, the open-source software SWIG is used to convert
C/C++ language in script language as Python or Java. The code, a demo and an
howto can be found on \url{https://www.github.com/nathanLoretan/FIR_Filter}.

To ease the compilation of the C++ class, a simple Makefile is created.

    $ cd /path/to/FIR_filter
    $ make

The makefile compiles the C++ class and create the python module. Then the python package can be simply improted in a script.

    from FIR_filter.fir_filter import FIR_filter

In the FIR_filter_demo.py, four FIR filters are created of each possible type.
A window function of hamming is used to improve those filters. The filters are
characterized by:
#. Sampling rate: 1kHz
#. Number of taps: 800
#. Low pass filter cut frequency: 50Hz
#. High pass filter cut frequency: 50Hz
#. Band pass filter cut frequencies: 50Hz - 100Hz
#. Stop band filter cut frequencies: 50Hz - 100Hz

Then, a signal composed with three frequencies, 10Hz, 75Hz and 150Hz, is created
and is filtered with the different type of FIR filter.
