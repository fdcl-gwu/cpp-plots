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