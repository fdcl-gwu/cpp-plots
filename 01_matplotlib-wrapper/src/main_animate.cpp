/*
The MIT License (MIT)

Copyright (c) 2014 Benno Evers

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#define _USE_MATH_DEFINES
#include <cmath>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main(void)
{
    int n = 1000;
    std::vector<double> x, y, z;

    for (int i = 0; i < n; i++)
    {
        x.push_back(i * i);
        y.push_back(sin(2 * M_PI * i / 360.0));
        z.push_back(log(i));

        if (i % 10 == 0)
        {
            plt::clf();  // clear previous plot
            plt::plot(x, y);
            plt::named_plot("log(x)", x, z);
            plt::xlim(0, n * n);
            plt::title("Sample figure");
            plt::legend();
            
            plt::pause(0.01);
        }
    }

    return 0;
}