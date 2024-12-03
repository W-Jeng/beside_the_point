# Beside the Point

## Jane Street November 2024 Puzzle Solution

### Problem Statement

*Two random points, one red and one blue, are chosen uniformly and independently from the interior of a square. To ten decimal places¹, what is the probability that there exists a point on the side of the square closest to the blue point that is equidistant to both the blue point and the red point?*

*(Or, if you want to send in the exact answer, that’s fine too!)*

### Solution Overview

Solving this problem using standard Monte Carlo methods would take over **3,000 years**. However, my optimized solution computes the probability in **under 2 seconds** by implementing several advanced numerical methods:

- **Monte Carlo**
- **Quadrature**
- **Simpson's Rule**
- **Adaptive Simpson's Rule**
- **Adaptive Boole's Rule**

### Implementation Details

The solution is implemented in C++ and utilizes CMake for building the project. Multiple numerical methods have been coded to provide both efficiency and accuracy in computing the required probability.

#### Numerical Methods Implemented

1. **Monte Carlo**
2. **Quadrature**
3. **Simpson's Rule**
4. **Adaptive Simpson's Rule**
5. **Adaptive Boole's Rule**

### Getting Started

#### Prerequisites

- **C++ Compiler**: Ensure you have a modern C++ compiler installed.
- **CMake**: Version 3.10 or higher.

#### Building the Project

1. **Clone the Repository**

    ```bash
    git clone https://github.com/yourusername/beside-the-point.git
    cd beside-the-point
    ```

2. **Create a Build Directory**

    ```bash
    mkdir build
    cd build
    ```

3. **Configure the Project with CMake**

    ```bash
    cmake -DCMAKE_BUILD_TYPE=Release ..
    ```

4. **Build the Executables**

    ```bash
    cmake --build .
    ```

    This will generate the following executables:

    - `monte_carlo`
    - `quad_triple`
    - `simpson_triple`
    - `adaptive_simpson`
    - `adaptive_boole`

#### Running the Executables

From the `build` directory, execute the desired method:

```bash
./monte_carlo
./quad_triple
./simpson_triple
./adaptive_simpson
./adaptive_boole
```

Solution From Adaptive Boole method up to 10 decimals accuracy
```bash
Adaptive Boole Result: 0.49140757886824131920
Time taken: 1949 milliseconds
```
