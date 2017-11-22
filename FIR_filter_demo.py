# -*- coding: utf-8 -*-
"""
Created on Tue Oct 03 23:39:34 2017

@author: Nathan Loretan
         MSc Computer System Engineering
         University of Glasgow

Digital Signal Processing
Assignment 2 Question 1
"""

import numpy as np
import matplotlib.pyplot as plt
from FIR_filter.fir_filter import FIR_filter

# Closes all figures
plt.close('all')

# ------------------------------------------------------------------------------

fs = 1000
f1 = 50.0  / fs
f2 = 100.0 / fs
m  = 800

# Create filter
filter_lp = FIR_filter(m, f1, 0,  "lp", "hamming")
filter_hp = FIR_filter(m, f1, 0,  "hp", "hamming")
filter_bp = FIR_filter(m, f1, f2, "bp", "hamming")
filter_sb = FIR_filter(m, f1, f2, "sb", "hamming")

# Get coefficient
h_lp = filter_lp.getCoefficients()
h_hp = filter_hp.getCoefficients()
h_bp = filter_bp.getCoefficients()
h_sb = filter_sb.getCoefficients()

# Get spectrum
hFFT_lp = np.fft.fft(h_lp)
hFFT_hp = np.fft.fft(h_hp)
hFFT_bp = np.fft.fft(h_bp)
hFFT_sb = np.fft.fft(h_sb)

# create x-axis
faxis = np.linspace(0, float(fs), m)

plt.figure("Low pass")
plt.plot(faxis, abs(hFFT_lp))
plt.grid(True)
plt.xlabel('f[Hz]', fontsize=16)
plt.ylabel('|X(f)|', fontsize=16)
plt.tight_layout()
plt.show()

plt.figure("High pass")
plt.plot(faxis, abs(hFFT_hp))
plt.grid(True)
plt.xlabel('f[Hz]', fontsize=16)
plt.ylabel('|X(f)|', fontsize=16)
plt.tight_layout()
plt.show()

plt.figure("Band pass")
plt.plot(faxis, abs(hFFT_bp))
plt.grid(True)
plt.xlabel('f[Hz]', fontsize=16)
plt.ylabel('|X(f)|', fontsize=16)
plt.tight_layout()
plt.show()

plt.figure("Stop band")
plt.plot(faxis, abs(hFFT_sb))
plt.grid(True)
plt.xlabel('f[Hz]', fontsize=16)
plt.ylabel('|X(f)|', fontsize=16)
plt.tight_layout()
plt.show()

# DEMO =========================================================================

t = np.linspace(0, 10, 10*fs)

f1_demo = 10.0   #Hz
f2_demo = 75.0   #Hz
f3_demo = 150.0  #Hz

signal = np.sin(2.0*np.pi*f1_demo*t)\
       + np.sin(2.0*np.pi*f2_demo*t)\
       + np.sin(2.0*np.pi*f3_demo*t)

signal_filtered_lp = np.zeros(len(signal))
signal_filtered_hp = np.zeros(len(signal))
signal_filtered_bp = np.zeros(len(signal))
signal_filtered_sb = np.zeros(len(signal))

for i in range(len(signal)):
    signal_filtered_lp[i] = filter_lp.filter(signal[i])
    signal_filtered_hp[i] = filter_hp.filter(signal[i])
    signal_filtered_bp[i] = filter_bp.filter(signal[i])
    signal_filtered_sb[i] = filter_sb.filter(signal[i])

# Get spectrum
signalFFT             = np.fft.fft(signal)
signal_filtered_lpFFT = np.fft.fft(signal_filtered_lp)
signal_filtered_hpFFT = np.fft.fft(signal_filtered_hp)
signal_filtered_bpFFT = np.fft.fft(signal_filtered_bp)
signal_filtered_sbFFT = np.fft.fft(signal_filtered_sb)

# create x-axis
faxis = np.linspace(0, float(fs), len(signal))

plt.figure("Signal spectrum")
plt.plot(faxis, abs(signalFFT))
plt.grid(True)
plt.xlabel('f[Hz]', fontsize=16)
plt.ylabel('|X(f)|', fontsize=16)
plt.tight_layout()
plt.show()

plt.figure("Signal spectrum, Low pass filtered")
plt.plot(faxis, abs(signal_filtered_lpFFT))
plt.grid(True)
plt.xlabel('f[Hz]', fontsize=16)
plt.ylabel('|X(f)|', fontsize=16)
plt.tight_layout()
plt.show()

plt.figure("Signal spectrum, High pass filtered")
plt.plot(faxis, abs(signal_filtered_hpFFT))
plt.grid(True)
plt.xlabel('f[Hz]', fontsize=16)
plt.ylabel('|X(f)|', fontsize=16)
plt.tight_layout()
plt.show()

plt.figure("Signal spectrum, Band pass filtered")
plt.plot(faxis, abs(signal_filtered_bpFFT))
plt.grid(True)
plt.xlabel('f[Hz]', fontsize=16)
plt.ylabel('|X(f)|', fontsize=16)
plt.tight_layout()
plt.show()

plt.figure("Signal spectrum, Stop band filtered")
plt.plot(faxis, abs(signal_filtered_sbFFT))
plt.grid(True)
plt.xlabel('f[Hz]', fontsize=16)
plt.ylabel('|X(f)|', fontsize=16)
plt.tight_layout()
plt.show()
