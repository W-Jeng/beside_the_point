#pragma once
#include "random_generator.h"
#include<iostream>
#include<iomanip>
#include<chrono>
#include<algorithm>
#include<stdlib.h>
#include "evaluation.h"
#include<cmath>
#include<math.h>
// solution to numerical triple integration
class QuadTriple {
public:
    const int INTEGRAL_POINTS_1;
    const int INTEGRAL_POINTS_2;
    const int INTEGRAL_POINTS_3;
    
    QuadTriple(const int& INTEGRAL_POINTS): INTEGRAL_POINTS_1{INTEGRAL_POINTS},
        INTEGRAL_POINTS_2{INTEGRAL_POINTS}, INTEGRAL_POINTS_3{INTEGRAL_POINTS} {};

    void solve() {
        auto start = std::chrono::high_resolution_clock::now();

        triple_integral_solution();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
        return;
    }

    void triple_integral_solution() {
        long long int total_function_eval = (long long int) INTEGRAL_POINTS_1 * INTEGRAL_POINTS_2 * INTEGRAL_POINTS_3;
        long double ans = 4.0 * integrate_1();
        std::cout << std::fixed << std::setprecision(30);
        std::cout << "Point Evaluated: " << total_function_eval << ", Integral: " << ans << std::endl;
        return;
    }

    long double eval_func(const double& x_r, const double& x_b, const double& y_b) {
        long double val1 = sqrtl(std::max(0.0, pow(y_b,2)+(x_r-x_b)*(2-(x_b+x_r))));
        long double val2 = sqrtl(std::max(0.0, pow(y_b,2)+(x_b+x_r)*(x_b-x_r)));
        return abs(val1-val2);
    }

    long double integrate_1() {
        // integrate over y_b
        const long double lower_bound = 0.0;
        const long double upper_bound = 0.5;
        const long double interval = (upper_bound-lower_bound)/INTEGRAL_POINTS_1;
        long double total_integral = 0.0;

        long double f_a = 0.5*integrate_2(lower_bound);
        long double f_b = 0.5*integrate_2(upper_bound);

        for (int i = 1; i <= INTEGRAL_POINTS_1-1; ++i) {
            total_integral += integrate_2(lower_bound + i * interval);
        }
        total_integral += (f_a + f_b);
        total_integral = total_integral * interval;
        return total_integral;
    }

    long double integrate_2(const double& y_b) {
        // integrate over x_b
        const long double lower_bound = y_b;
        const long double upper_bound = 1-y_b;
        const long double interval = (upper_bound-lower_bound)/INTEGRAL_POINTS_2;
        long double total_integral = 0.0;

        long double f_a = 0.5*integrate_3(lower_bound, y_b);
        long double f_b = 0.5*integrate_3(upper_bound, y_b);

        for (int i = 1; i <= INTEGRAL_POINTS_2-1; ++i) {
            total_integral += integrate_3(lower_bound + i * interval, y_b);
        }
        total_integral += (f_a + f_b);
        // std::cout << std::fixed << std::setprecision(15);
        // std::cout << "\ti2: y_b: " << y_b << ", total integral: " << total_integral << std::endl;
        total_integral = total_integral * interval;
        return total_integral;
    }

    long double integrate_3(const double& x_b, const double& y_b) {
        // integrate over x_r
        const long double lower_bound = 0.0;
        const long double upper_bound = 1.0;
        const long double interval = (upper_bound-lower_bound)/INTEGRAL_POINTS_3;
        long double total_integral = 0.0;
        
        // implement quadrature rules
        // if we have n subintervals, then we need to evaluate n+1 points
        // including 0th and last points
        // first point
        long double f_a = 0.5*eval_func(lower_bound, x_b, y_b);
        // last point
        long double f_b = 0.5*eval_func(upper_bound, x_b, y_b);

        for (int i = 1; i <= INTEGRAL_POINTS_3-1; ++i) {
            total_integral += eval_func(lower_bound + i * interval,
                x_b, y_b);
        }
        total_integral += (f_a + f_b); 
        // std::cout << std::fixed << std::setprecision(15);
        // std::cout << "i3: x_b: " << x_b << ", y_b: " << y_b << ", total_integral: " << total_integral << std::endl;
        total_integral = total_integral * interval;
        return total_integral;
    }
};