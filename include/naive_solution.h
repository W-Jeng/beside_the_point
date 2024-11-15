#pragma once
#include "random_generator.h"
#include<iostream>
#include<iomanip>
#include<chrono>
#include "evaluation.h"

class NaiveSolution {
public:
    long int evaluated_instance;
    long int is_equidistant_instance; // this is always equivalent or lower than evaluated instance
    const long int number_of_runs{100000000};
    const long int output_every{1000000};
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
            Point p1(rg.generate(), rg.generate());
            Point p2(rg.generate(), rg.generate());
            ++evaluated_instance;
            if (is_equidistant(p1, p2)) {
                ++is_equidistant_instance;
            }
            // if (evaluated_instance % output_every == 0) {
            //     std::cout << "\rRuns: " << evaluated_instance << ", is_equidistant instances: "<<
            //         is_equidistant_instance << ", prob: " << static_cast<double>(is_equidistant_instance)/evaluated_instance;
            // }
        }
        
        std::cout << "\rRuns: " << evaluated_instance << ", is_equidistant instances: "<<
                    is_equidistant_instance << ", prob: " << static_cast<double>(is_equidistant_instance)/evaluated_instance;
        
        std::cout << std::endl;
    }
};