from z3 import *

if __name__ == "__main__":
    x = Int('x')
    y = Int('y')
    s = Solver()
    s.add(x + y > 5, Not(x + y > 5))
    status = s.check()
    print status
    if status == 'sat':
        print s.model()

