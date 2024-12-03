#include <iostream>
#include <iomanip>
#include "random_generator.h"
#include "adaptive_boole_quad.h"
#include<vector>
#include<cmath>

int main() {
    // adaptive way, inner integrals evaluated using boole, and extrapolated using boole method
    const long double tolerance2 = pow(10.0L, -10.0L);
    AdaptiveBooleQuad abq(tolerance2);
    abq.solve();
    return 0;
}