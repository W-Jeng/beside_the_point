import numpy as np

def eval_func(x_r, x_b, y_b):
    """Evaluates the function for the integral."""
    val1 = np.sqrt(max(0, y_b**2 + (x_r - x_b) * (2 - (x_b + x_r))))
    val2 = np.sqrt(max(0, y_b**2 + (x_b + x_r) * (x_b - x_r)))
    return abs(val1 - val2)

def integrate_3(x_b, y_b, num_points=100):
    """Integrates over x_r."""
    lower_bound = 0.0
    upper_bound = 1.0
    interval = (upper_bound - lower_bound) / num_points
    total_integral = 0.0

    # Apply trapezoidal rule
    total_integral += 0.5 * eval_func(lower_bound, x_b, y_b)
    total_integral += 0.5 * eval_func(upper_bound, x_b, y_b)

    for i in range(1, num_points):
        x_r = lower_bound + i * interval
        total_integral += eval_func(x_r, x_b, y_b)

    # print(f"i3: x_b:{x_b}, y_b:{y_b}, total_integral:{total_integral}")
    return total_integral * interval

def integrate_2(y_b, num_points=100):
    """Integrates over x_b."""
    lower_bound = y_b
    upper_bound = 1 - y_b
    interval = (upper_bound - lower_bound) / num_points
    total_integral = 0.0

    # Apply trapezoidal rule
    total_integral += 0.5 * integrate_3(lower_bound, y_b, num_points)
    total_integral += 0.5 * integrate_3(upper_bound, y_b, num_points)
    for i in range(1, num_points):
        x_b = lower_bound + i * interval
        total_integral += integrate_3(x_b, y_b, num_points)
    
    # print(f"\ti2: y_b: {y_b}, total integral: {total_integral}")
    return total_integral * interval

def integrate_1(num_points=100):
    """Integrates over y_b."""
    lower_bound = 0.0
    upper_bound = 0.5
    interval = (upper_bound - lower_bound) / num_points
    total_integral = 0.0

    # Apply trapezoidal rule
    total_integral += 0.5 * integrate_2(lower_bound, num_points)
    total_integral += 0.5 * integrate_2(upper_bound, num_points)
    for i in range(1, num_points):
        y_b = lower_bound + i * interval
        total_integral += integrate_2(y_b, num_points)
    
    return total_integral * interval

def total_probability():
    """Compute the total probability."""
    return 4 * integrate_1()

# Run the calculation
if __name__ == "__main__":
    result = total_probability()
    print(f"Total Probability: {result:.10f}")
