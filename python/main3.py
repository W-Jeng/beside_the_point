import numpy as np

# Functions for y_r^2 bounds based on x_r > x_b and x_r < x_b
def y_r2_bounds_xr_gt_xb(x_b, y_b, x_r):
    """Calculate the bounds for y_r^2 when x_r > x_b."""
    y_r2_min = y_b**2 - (x_b + x_r) * (x_r - x_b)
    y_r2_max = y_b**2 + 2 * (x_r - x_b) * (1 - (x_b + x_r) / 2)
    return max(0, y_r2_min), max(0, y_r2_max)  # Ensure non-negative bounds

def y_r2_bounds_xr_lt_xb(x_b, y_b, x_r):
    """Calculate the bounds for y_r^2 when x_r < x_b."""
    y_r2_min = y_b**2 + 2 * (x_r - x_b) * (1 - (x_b + x_r) / 2)
    y_r2_max = y_b**2 - (x_b + x_r) * (x_r - x_b)
    return max(0, y_r2_min), max(0, y_r2_max)  # Ensure non-negative bounds

# Outer integration bounds for x_b and y_b
def x_b_min(y_b):
    return y_b

def x_b_max(y_b):
    return 1 - y_b

# Calculate the area of valid y_r values
def y_r_area(x_b, y_b, x_r, x_r_gt_xb=True):
    """Calculate the area of valid y_r values."""
    if x_r_gt_xb:
        y_r2_min, y_r2_max = y_r2_bounds_xr_gt_xb(x_b, y_b, x_r)
    else:
        y_r2_min, y_r2_max = y_r2_bounds_xr_lt_xb(x_b, y_b, x_r)

    if y_r2_min > y_r2_max:
        return 0  # Invalid range
    return max(0, np.sqrt(y_r2_max)) - max(0, np.sqrt(y_r2_min))

# Integration routine
def integrate_bottom_with_sqrt(dy_b=0.001, dx_b=0.001, dx_r=0.001):
    """Numerically compute P_bottom with correct square root handling."""
    p_bottom = 0
    y_b = 0
    while y_b <= 0.5:  # Integrate over y_b
        x_b_min_val = x_b_min(y_b)
        x_b_max_val = x_b_max(y_b)
        x_b = x_b_min_val
        while x_b <= x_b_max_val:  # Integrate over x_b
            x_r = 0
            while x_r <= 1:  # Integrate over x_r
                if x_r > x_b:
                    contribution = y_r_area(x_b, y_b, x_r, x_r_gt_xb=True)
                else:
                    contribution = y_r_area(x_b, y_b, x_r, x_r_gt_xb=False)
                if contribution > 0:
                    p_bottom += contribution * dx_r * dx_b * dy_b
                x_r += dx_r
            x_b += dx_b
        y_b += dy_b
    return 4 * p_bottom  # Multiply by 4 for total probability

# Total probability
def total_probability():
    """Compute the total probability by integrating P_bottom."""
    return integrate_bottom_with_sqrt()

# Run the calculation
if __name__ == "__main__":
    result = total_probability()
    print(f"Total Probability: {result:.6f}")
