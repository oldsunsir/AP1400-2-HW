#ifndef Q1_H
#define Q1_H
#include<cmath>
#include<functional>

namespace q1 {

    double gradient_descent(double init, double step, std::function<double(double)> func);

    template<typename T, typename F>
    T gradient_descent(double init, double step) {
        return gradient_descent(init, step, F());
    }

    double gradient_descent(double init, double step, std::function<double(double)> f) {
        double x{ init };
        double g{ (f(x + 0.00001) - f(x)) / 0.00001 };
        while (abs(g) > 0.00001) {
            x -= step * g;
            g = (f(x + 0.00001) - f(x)) / 0.00001;
        }
        return x;
    }
}


#endif