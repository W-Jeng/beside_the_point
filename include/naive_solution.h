#pragma once
#include "random_generator.h"
#include<iostream>
#include<iomanip>
#include<chrono>

class NaiveSolution {
public:
    const double min_edge = 0.0;
    const double max_edge = 1.0;

    long int evaluated_instance;
    long int is_equidistant_instance; // this is always equivalent or lower than evaluated instance
    const long int number_of_runs{1000000};
    RandomGenerator rg;
    
    NaiveSolution(): evaluated_instance(0),
        is_equidistant_instance(0), rg() {}

    void solve() {
        auto start = std::chrono::high_resolution_clock::now();

        loop();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
        return;
    }

    void loop() {
        for (long int i = 0; i < number_of_runs; ++i) {
            double temp = rg.generate();
        }
    }
};