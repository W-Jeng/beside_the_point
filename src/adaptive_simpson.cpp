#include <iostream>
#include <iomanip>
#include "random_generator.h"
#include "adaptive_quad.h"
#include<vector>
#include<cmath>

int main() {
    const long double tolerance1 = pow(10L, -10.0L);
    AdaptiveQuad aq(tolerance1);
    aq.solve();

    return 0;
}