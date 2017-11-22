#include "fir_filter.h"

static double sinc(const double x)
{
    if (x == 0)
        return 1;

    return sin(M_PI * x) / (M_PI * x);
}

FIR_filter::FIR_filter( int taps, double f1, double f2, char* type,
                        char* window): h(taps, 0), samples(taps, 0)
{
    this->idx     = 0;
    this->taps    = taps;

    std::vector<double> h;  // Buffer FIR coefficients
    std::vector<double> w;  // Buffer window coefficients

    // Calculate the coefficient corresponding to the filter type
    if (!strcmp(type, "lp")) {
        h = lowPass_coefficient(taps, f1);
    }
    else if (!strcmp(type, "hp")) {
        h = highPass_coefficient(taps, f1);
    }
    else if (!strcmp(type, "bp")) {
        h = bandPass_coefficient(taps, f1, f2);
    }
    else if (!strcmp(type, "sb")) {
        h = bandStop_coefficient(taps, f1, f2);
    }

    // Calculate the window to improve the FIR filter
    if (!strcmp(window, "hamming")) {
        w = window_hammig(taps);
    }
    else if (!strcmp(window, "triangle")) {
        w = window_triangle(taps);
    }
    else if (!strcmp(window, "hanning")) {
        w = window_hanning(taps);
    }
    else if (!strcmp(window, "blackman")) {
        w = window_blackman(taps);
    }

    if (!strcmp(window, "")) {
        this->h = h;
    }
    else
    {
        for(int n = 0; n < taps; n++) {
            this->h[n] = h[n] * w[n];
        }
    }
}

FIR_filter::~FIR_filter()
{

}

std::vector<double> FIR_filter::getCoefficients()
{
    return this->h;
}

std::vector<double> FIR_filter::lowPass_coefficient(int taps, double f)
{
    std::vector<int>    n(taps, 0);
    std::vector<double> h(taps, 0);

    for(int i = 0; i < taps; i++) {
        n[i] = i - int(taps/2);
    }

    for(int i = 0; i < taps; i++) {
        h[i] = 2.0*f*sinc(2.0*f*n[i]);
    }

    return h;
}

std::vector<double> FIR_filter::highPass_coefficient(int taps, double f)
{
    std::vector<int>    n(taps, 0);
    std::vector<double> h(taps, 0);

    for(int i = 0; i < taps; i++) {
        n[i] = i - int(taps/2);
    }

    for(int i = 0; i < taps; i++) {
        h[i] = sinc(n[i]) - 2.0*f*sinc(2.0*f*n[i]);
    }

    return h;
}

std::vector<double> FIR_filter::bandPass_coefficient(int taps, double f1, double f2)
{
    std::vector<int>    n(taps, 0);
    std::vector<double> h(taps, 0);

    for(int i = 0; i < taps; i++) {
        n[i] = i - int(taps/2);
    }

    for(int i = 0; i < taps; i++) {
        h[i] = 2.0*f1*sinc(2.0*f1*n[i]) - 2.0*f2*sinc(2.0*f2*n[i]);
    }

    return h;
}

std::vector<double> FIR_filter::bandStop_coefficient(int taps, double f1, double f2)
{
    std::vector<int>    n(taps, 0);
    std::vector<double> h(taps, 0);

    for(int i = 0; i < taps; i++) {
        n[i] = i - int(taps/2);
    }

    for(int i = 0; i < taps; i++) {
        h[i] = 2.0*f1*sinc(2.0*f1*n[i]) - 2.0*f2*sinc(2.0*f2*n[i]) + sinc(n[i]);
    }

    return h;
}

std::vector<double> FIR_filter::window_hammig(int taps)
{
    std::vector<int>    n(taps, 0);
    std::vector<double> w(taps, 0);

    double alpha   = 0.54;
    double beta    = 0.46;

    for(int i = 0; i < taps; i++) {
        w[i] = alpha - beta * cos(2.0 * M_PI * i / (taps - 1));
    }

    return w;
}

std::vector<double> FIR_filter::window_hanning(int taps)
{
    std::vector<double> w(taps, 0);

    for(int i = 0; i < taps; i++) {
        w[i] =  sin(((double) M_PI * i) / (taps - 1)) *
                sin(((double) M_PI * i) / (taps - 1));
    }

    return w;
}

std::vector<double> FIR_filter::window_triangle(int taps)
{
    std::vector<double> w(taps, 0);

    double l = taps;

    for(int i = 0; i < taps; i++) {
        w[i] = 1 - abs((i - (((double)(taps-1)) / 2.0)) / (((double)l) / 2.0));
    }

    return w;
}

std::vector<double> FIR_filter::window_blackman(int taps)
{
    std::vector<double> w(taps, 0);

    double alpha0 = 0.42;
    double alpha1 = 0.5;
    double alpha2 = 0.08;

    for(int i = 0; i < taps; i++) {
        w[i] = alpha0 - alpha1 * cos(2.0 * M_PI * i / (taps - 1))
                      - alpha2 * cos(4.0 * M_PI * i / (taps - 1));
    }

    return w;
}

double FIR_filter::filter(double new_sample)
{
    double result = 0;

    // Save the new sample
    this->samples[this->idx] = new_sample;

    // Calculate the output
    for(int n = 0; n < this->taps; n++)
        result += this->samples[(this->idx + n) % this->taps] * this->h[n];

    // Increase the round robin index
    this->idx = (this->idx + 1) % this->taps;

    return result;
}
