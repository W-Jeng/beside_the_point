import numpy as np

num_trials = 100000000
successful_cases = 0

# (Use GPU guys, this is just an idea)
def step(x1, x2, y1, y2):
    m = - (x2 - x1) / (y2 - y1) 

    if ((1 - y1) < (1 - x1)) and ((1 - y1) < (x1)) and ((1 - y1) < (y1)):
        up = (1 - (y1 + y2) / 2 ) / m + (x1 + x2) / 2 
        if up >= 0 and up <= 1:
            return 1
        
    if ((x1) < (1 - y1)) and ((x1) < (1 - x1)) and ((x1) < (y1)):
        left = - m * (x1 + x2) / 2 + (y1 + y2) / 2
        if left >= 0 and left <= 1:
            return 1

    if ((y1) < (x1)) and ((y1) < (1 - y1)) and ((y1) < (1 - x1)):
        down = - (y1 + y2) / (2 * m) + (x1 + x2) / 2
        if down >= 0 and down <= 1:
            return 1

    if ((1 - x1) < (x1)) and ((1 - x1) < (1 - y1)) and ((1 - x1) < (y1)):
        right = m * (1 - (x1 + x2) / 2) + (y1 + y2) / 2
        if right >= 0 and right <= 1:
            return 1
        
    return 0

for i in range(num_trials):
    successful_cases += step(np.random.rand(), np.random.rand(), np.random.rand(), np.random.rand())

print(successful_cases / num_trials)