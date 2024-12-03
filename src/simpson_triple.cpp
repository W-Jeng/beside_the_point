#include <iostream>
#include <iomanip>
#include "random_generator.h"
#include "simpson_triple.h"
#include<vector>
#include<cmath>

int main() {
    SimpsonTriple st(512);
    st.solve();

    return 0;
}