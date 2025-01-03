#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <stdexcept>

class AdaptiveBooleQuad {
public:
    const int INTEGRAL_POINTS_1{4}; // Number of subintervals for y_b
    const int INTEGRAL_POINTS_2{4}; // Number of subintervals for x_b
    const int INTEGRAL_POINTS_3{4}; // Number of subintervals for x_r
    const long double min_tolerance{pow(10.0L, -20.0L)};
    const long double tolerance;    // Desired accuracy

    AdaptiveBooleQuad(const long double& t_tolerance): tolerance{t_tolerance} {
        // change the integral points such that it is in multiplier of 4
        if (INTEGRAL_POINTS_1 % 4 != 0 ||
            INTEGRAL_POINTS_2 % 4 != 0 ||
            INTEGRAL_POINTS_3 % 4 != 0) {
            throw std::runtime_error("Integral points must be divisible by 4");
        }
    };

    void solve() {
        auto start = std::chrono::high_resolution_clock::now();

        triple_integral_solution();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
        return;
    }

    void triple_integral_solution() {
        long double result = 4.0*integrate_1(0.0, 0.5, tolerance);
        std::cout << std::fixed << std::setprecision(20);
        std::cout << "Adaptive Boole Result: " << result << std::endl;
    }

    long double eval_func(const long double& x_r, const long double& x_b, const long double& y_b) {
        long double val1 = sqrtl(std::max(0.0L, pow(y_b, 2) + (x_r - x_b) * (2.0 - (x_b + x_r))));
        long double val2 = sqrtl(std::max(0.0L, pow(y_b, 2) + (x_b + x_r) * (x_b - x_r)));
        return fabsl(val1 - val2);
    }

    inline long double eval_func2(long double x_r, long double x_b, long double y_b) {
        long double yb_sq = y_b * y_b;

        // Precompute commonly used expressions
        long double x_b_plus_x_r = x_b + x_r;
        long double x_b_minus_x_r = x_b - x_r;
        long double two_minus_x_b_plus_x_r = 2.0L - x_b_plus_x_r;

        // Compute expr1 with branch elimination
        long double expr1 = yb_sq + (x_r - x_b) * two_minus_x_b_plus_x_r;
        expr1 = (expr1 > 0.0L) ? expr1 : 0.0L;
        long double val1 = sqrtl(expr1);

        // Compute expr2 with branch elimination
        long double expr2 = yb_sq + x_b_plus_x_r * x_b_minus_x_r;
        expr2 = (expr2 > 0.0L) ? expr2 : 0.0L;
        long double val2 = sqrtl(expr2);

        // Return the absolute difference
        return fabsl(val1 - val2);
    }

    long double integrate_1(const long double& lower_bound, const long double& upper_bound, const long double& tol) {
        long double mid = (lower_bound + upper_bound) / 2.0;
        long double whole = composite_boole_1(lower_bound, upper_bound, tol);
        long double left = composite_boole_1(lower_bound, mid, tol/2.0);
        long double right = composite_boole_1(mid, upper_bound, tol/2.0);

        if (fabsl(left + right - whole) <= std::max(63.0*tol, min_tolerance)) {
            return (left+right) + (left+right-whole)/63.0L; // Richardson extrapolation
        }

        return integrate_1(lower_bound, mid, tol / 2.0) + integrate_1(mid, upper_bound, tol / 2.0);
    }

    long double composite_boole_1(const long double& lower_bound, const long double& upper_bound,
        const long double& tol) {
        const long double h = (upper_bound - lower_bound) / INTEGRAL_POINTS_1;
        const long double tol_reduced = (tol/std::sqrt(INTEGRAL_POINTS_1));
        long double sum = 7.0*(integrate_2(lower_bound, lower_bound, 1.0-lower_bound, tol_reduced) +
                          integrate_2(upper_bound, upper_bound, 1.0-upper_bound, tol_reduced));

        for (int i = 1; i < INTEGRAL_POINTS_1; ++i) {
            long double x = lower_bound + i * h;
            if (i % 2 == 1) {
                sum += 32.0*integrate_2(x, x, 1.0-x, tol_reduced);
            } else if ((i+2) % 4 == 0) {
                sum += 12.0*integrate_2(x, x, 1.0-x, tol_reduced);
            } else {
                sum += 14.0*integrate_2(x, x, 1.0-x, tol_reduced);
            }
        }

        return ((2.0*h)/45.0) * sum;
    }

    long double integrate_2(const long double& y_b, const long double& lower_bound,
        const long double& upper_bound, const long double& tol) {

        long double mid = (lower_bound + upper_bound) / 2.0;
        long double whole = composite_boole_2(y_b, lower_bound, upper_bound, tol);
        long double left = composite_boole_2(y_b, lower_bound, mid, tol/2.0);
        long double right = composite_boole_2(y_b, mid, upper_bound, tol/2.0);

        if (fabsl(left + right - whole) <= std::max(63.0*tol, min_tolerance)) {
            return (left+right) + (left+right-whole)/63.0L; // Richardson extrapolation
        }

        return integrate_2(y_b, lower_bound, mid, tol / 2.0) + integrate_2(y_b, mid, upper_bound, tol / 2.0);
    }

    long double composite_boole_2(const long double& y_b, const long double& lower_bound,
        const long double& upper_bound, const long double& tol) {

        const long double h = (upper_bound - lower_bound) / INTEGRAL_POINTS_2;
        const long double tol_reduced = (tol/std::sqrt(INTEGRAL_POINTS_2));
        long double sum = 7.0*(integrate_3(lower_bound, y_b, 0.0, 1.0, tol_reduced) +
                          integrate_3(upper_bound, y_b, 0.0, 1.0, tol_reduced));

        for (int i = 1; i < INTEGRAL_POINTS_2; ++i) {
            long double x = lower_bound + i * h;
            if (i % 2 == 1) {
                sum += 32.0*integrate_3(x, y_b, 0.0, 1.0, tol_reduced);
            } else if ((i+2) % 4 == 0) {
                sum += 12.0*integrate_3(x, y_b, 0.0, 1.0, tol_reduced);
            } else {
                sum += 14.0*integrate_3(x, y_b, 0.0, 1.0, tol_reduced);
            }
        }

        return ((2.0*h)/45.0) * sum;
    }

    long double integrate_3(const long double& x_b, const long double& y_b,
        const long double& lower_bound, const long double& upper_bound, const long double& tol) {
        
        long double mid = (lower_bound + upper_bound)/2.0;
        long double whole = composite_boole_3(x_b, y_b, lower_bound, upper_bound);
        long double left = composite_boole_3(x_b, y_b, lower_bound, mid);
        long double right = composite_boole_3(x_b, y_b, mid, upper_bound);

        if (fabsl(left+right-whole) <= std::max(63.0*tol, min_tolerance)) {
            return (left+right) + (left+right-whole)/63.0L; // Richardson extrapolation
        }

        return integrate_3(x_b, y_b, lower_bound, mid, tol/2.0)+
            integrate_3(x_b, y_b, mid, upper_bound, tol/2.0);
    }

    long double composite_boole_3(const long double& x_b, const long double& y_b,
        const long double& lower_bound, const long double& upper_bound) {
        
        const long double h = (upper_bound - lower_bound) / INTEGRAL_POINTS_3;
        long double sum = 7.0*(eval_func2(lower_bound, x_b, y_b) + eval_func2(upper_bound, x_b, y_b));

        for (int i = 1; i < INTEGRAL_POINTS_3; ++i) {
            long double x = lower_bound + i * h;

            if (i % 2 == 1) {
                sum += 32.0*eval_func2(x, x_b, y_b);
            } else if ((i+2) % 4 == 0) {
                sum += 12.0*eval_func2(x, x_b, y_b);
            } else {
                sum += 14.0*eval_func2(x, x_b, y_b);
            }
        }

        return ((2.0*h)/45.0) * sum;
    }
};
