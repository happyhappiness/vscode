from z3 import *

if __name__ == "__main__":
    
    s = Solver()
    s.push()
    int_a, int_b = Bools('int int')
    func_a, func_b = Bools('func func')
    null_a, null_b = Bools('null null')
    stmt_one = Or(And(int_a, func_a), null_a)
    stmt_two = And(Or(int_b, null_b), Or(func_b, null_b))
    # decide whether two statement is equal
    s.add( Xor(stmt_one, stmt_two) )
    status = s.check()
    print status
    if status.r == 1:
        print s.model()
    else:
        print "stmt one <=> stmt two"
    s.pop()
