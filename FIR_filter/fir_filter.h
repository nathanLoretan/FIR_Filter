#ifndef FIR_FILTER_H
#define FIR_FILTER_H

#include <stdlib.h>
#include <cmath>
#include <string.h>
#include <string.h>
#include <vector>

class FIR_filter
{
public:
    FIR_filter( int taps=0, double f1=0, double f2=0, char* type="", 
                char* window="");
    ~FIR_filter();

    std::vector<double> getCoefficients();

    double filter(double new_sample);

private:
    std::vector<double> lowPass_coefficient( int taps, double f);
    std::vector<double> highPass_coefficient(int taps, double f);
    std::vector<double> bandPass_coefficient(int taps, double f1, double f2);
    std::vector<double> bandStop_coefficient(int taps, double f1, double f2);

    std::vector<double> window_hammig(int taps);
    std::vector<double> window_triangle(int taps);
    std::vector<double> window_hanning(int taps);
    std::vector<double> window_blackman(int taps);

    std::vector<double> h;       // FIR coefficients
    std::vector<double> samples; // FIR delay

    int idx;        // Round robin index
    int taps;       // Number of taps of the filter
};


#endif // FIR_FILTER_H
