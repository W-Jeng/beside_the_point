def adaptive_quadrature(f, a, b, tol=1e-8):
    """
    Adaptive Quadrature using Simpson's Rule.
    
    Args:
    - f: Function to integrate.
    - a, b: Integration bounds.
    - tol: Desired accuracy.
    
    Returns:
    - Integral of f over [a, b].
    """
    def simpson_rule(f, a, b):
        """Compute integral using Simpson's Rule over [a, b]."""
        mid = (a + b) / 2
        return (b - a) / 6 * (f(a) + 4 * f(mid) + f(b))
    
    def recursive_quad(f, a, b, tol, whole):
        """Recursive adaptive quadrature."""
        mid = (a + b) / 2
        left = simpson_rule(f, a, mid)
        right = simpson_rule(f, mid, b)
        if abs(left + right - whole) <= 15 * tol:
            return left + right + (left + right - whole) / 15  # Richardson extrapolation
        return recursive_quad(f, a, mid, tol / 2, left) + recursive_quad(f, mid, b, tol / 2, right)
    
    whole = simpson_rule(f, a, b)
    return recursive_quad(f, a, b, tol, whole)

# Example usage:
if __name__ == "__main__":
    import math
    result = adaptive_quadrature(math.exp, 0, 1, tol=1e-10)
    print(f"Result: {result:.10f}")
