import numpy as np

# Define the function for the integrand with fixed handling of invalid sqrt values
def integrand_fixed(x_b, y_b, x_r):
    # Calculate the bounds for y_r based on x_b, y_b, and x_r
    
    term_a = np.sqrt(max(0, y_b**2 + (x_r-x_b)*(2-(x_b+x_r))))
    term_b = np.sqrt(max(0, y_b**2 + (x_b+x_r)*(x_b-x_r)))
    
    return abs(term_a - term_b)

# Integration limits
y_b_min, y_b_max = 0, 0.5
x_b_min_func = lambda y_b: y_b
x_b_max_func = lambda y_b: 1 - y_b
x_r_min, x_r_max = 0, 1

# Resolution for numerical integration
dy_b = 0.001
dx_b = 0.001
dx_r = 0.001

# Initialize total integral
total_integral = 0

# Outer loop over y_b
y_b = y_b_min
while y_b <= y_b_max:
    # Middle loop over x_b
    x_b_min = x_b_min_func(y_b)
    x_b_max = x_b_max_func(y_b)
    x_b = x_b_min
    while x_b <= x_b_max:
        # Inner loop over x_r
        x_r = x_r_min
        while x_r <= x_r_max:
            total_integral += integrand_fixed(x_b, y_b, x_r)
            x_r += dx_r
        x_b += dx_b
    y_b += dy_b
total_integral = total_integral * dx_r * dx_b * dy_b

# Multiply by 4 for all sides
total_integral *= 4

# Output the result
print(f"Total integral: {total_integral}")
