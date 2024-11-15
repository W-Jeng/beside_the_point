#pragma once
#include "random_generator.h"
#include<iostream>
#include<iomanip>
#include<chrono>
#include<algorithm>
#include<stdlib.h>
#include "evaluation.h"
#include<cmath>

// solution to numerical triple integration
class QuadTriple {
public:
    const int INTEGRAL_POINTS_1{5000};
    const int INTEGRAL_POINTS_2{5000};
    const int INTEGRAL_POINTS_3{5000};
    
    QuadTriple() {};

    void solve() {
        auto start = std::chrono::high_resolution_clock::now();

        triple_integral_solution();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
        return;
    }

    void triple_integral_solution() {
        long long int total_function_eval = INTEGRAL_POINTS_1 * INTEGRAL_POINTS_2 * INTEGRAL_POINTS_3;
        double ans = 4.0 * integrate_1();
        std::cout << std::fixed << std::setprecision(15);
        std::cout << "Point Evaluated: " << total_function_eval << ", Integral: " << ans << std::endl;
        return;
    }

    double eval_func(const double& x_r, const double& x_b, const double& y_b) {
        double val1 = std::sqrt(std::max(0.0, pow(y_b,2)+(x_r-x_b)*(2-(x_b+x_r))));
        double val2 = std::sqrt(std::max(0.0, pow(y_b,2)+(x_b+x_r)*(x_b-x_r)));
        return abs(val1-val2);
    }

    double integrate_1() {
        // integrate over y_b
        const double lower_bound = 0.0;
        const double upper_bound = 0.5;
        const double interval = (upper_bound-lower_bound)/INTEGRAL_POINTS_1;
        double total_integral = 0.0;

        double f_a = 0.5*integrate_2(lower_bound);
        double f_b = 0.5*integrate_2(lower_bound);

        for (int i = 1; i <= INTEGRAL_POINTS_1-1; ++i) {
            total_integral += integrate_2(lower_bound + i * interval);
        }
        total_integral += (f_a + f_b);
        total_integral = total_integral * interval;
        return total_integral;
    }

    double integrate_2(const double& y_b) {
        // integrate over x_b
        const double lower_bound = y_b;
        const double upper_bound = 1-y_b;
        const double interval = (upper_bound-lower_bound)/INTEGRAL_POINTS_2;
        double total_integral = 0.0;

        double f_a = 0.5*integrate_3(lower_bound, y_b);
        double f_b = 0.5*integrate_3(upper_bound, y_b);

        for (int i = 1; i <= INTEGRAL_POINTS_2-1; ++i) {
            total_integral += integrate_3(lower_bound + i * interval, y_b);
        }
        total_integral += (f_a + f_b);
        total_integral = total_integral * interval;
        return total_integral;
    }

    double integrate_3(const double x_b, const double& y_b) {
        // integrate over x_r
        const double lower_bound = 0.0;
        const double upper_bound = 1.0;
        const double interval = (upper_bound-lower_bound)/INTEGRAL_POINTS_3;
        double total_integral = 0.0;
        
        // implement quadrature rules
        // if we have n subintervals, then we need to evaluate n+1 points
        // including 0th and last points
        // first point
        double f_a = 0.5*eval_func(lower_bound, x_b, y_b);
        // last point
        double f_b = 0.5*eval_func(upper_bound, x_b, y_b);

        for (int i = 1; i <= INTEGRAL_POINTS_3-1; ++i) {
            total_integral += eval_func(lower_bound + i * interval,
                x_b, y_b);
        }
        total_integral += (f_a + f_b); 
        total_integral = total_integral * interval;
        return total_integral;
    }
};