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

    // Adaptive Quad Result: 0.49140757883909140239
    // Time taken: 242853 milliseconds
    const long double tolerance1 = pow(10L, -10.0L);
    AdaptiveQuad aq(tolerance1);
    aq.solve();


    // adaptive way, inner integrals evaluated using boole, and extrapolated using boole method
    // const long double tolerance2 = pow(10.0L, -13.0L);
    // AdaptiveBooleQuad abq(tolerance2);
    // abq.solve();
    return 0;
}