#pragma once
#include <random>

class RandomGenerator {
public:
    RandomGenerator(): rd(), gen(rd()), dist(0.0, 1.0) {}

    double generate() {
        return dist(gen);
    }

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dist;
};