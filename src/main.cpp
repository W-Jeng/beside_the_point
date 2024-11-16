#include <iostream>
#include <iomanip>
#include "random_generator.h"
#include "naive_solution.h"
#include "quad_triple.h"
#include "simpson_triple.h"
#include "adaptive_quad.h"
#include "adaptive_boole_quad.h"
#include<vector>
#include<cmath>

int main() {
    // NaiveSolution ns;
    // ns.solve();

    // long int points = 4;
    // long int multiplier = 2;

    // for (int i = 0; i <= 9; ++i) {
    //     int integral_points = static_cast<int>(points * std::pow(multiplier, i));
    //     std::cout << "Integral points: " << integral_points << std::endl; 
    //     // QuadTriple qt(integral_points);
    //     // qt.solve();
    //     SimpsonTriple st(integral_points);
    //     st.solve();
    // }

    // const long double tolerance1 = pow(10, -6);
    // AdaptiveQuad aq(tolerance1);
    // aq.solve();

    const long double tolerance2 = pow(10.0L, -13.0L);
    AdaptiveBooleQuad abq(tolerance2);
    abq.solve();
    return 0;
}