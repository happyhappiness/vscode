import re
from z3 import *
import my_constant

"""
@ param postfix_expr(List)
@ return infix expression
@ involve transform postfix(list) expression into infix one(input for z3)
"""
def get_infix_for_postfix(postfix_expr):  
    infix_expr = []
    for token in postfix_expr:
        if token in ['==', '>', '>=', '!=', '<', '<=','&&', '||']:
            op_right = infix_expr.pop()
            op_left = infix_expr.pop()
            result = get_infix_for_binary_operator(token, op_left, op_right)
            infix_expr.append(result)
        elif token == '!':
            op = infix_expr.pop()
            result = get_infix_for_unary_operator(op)
            infix_expr.append(result)
        elif token != my_constant.JOERN_UNARY_OPERATOR:
            infix_expr.append(token)
    
    return infix_expr

"""
@ param operand
@ return infix expression
@ involve deal with !, Not(op)
"""
def get_infix_for_unary_operator(operand):
    # !p normalized to Not(p == null)
    operand = normalize_operand(operand)
    return Not(operand)

"""
@ param operand left and right
@ return infix expression
@ involve deal with binary operator (==, >, >=) (&&, or)
"""
def get_infix_for_binary_operator(op, op_left, op_right):

    if op == "==":
        # normalization == operands order
        op_left, op_right = order_operands(op_left, op_right)
        op_left = Int(op_left + '_e_l')
        op_right = Int(op_right + '_e_r')
        return op_left == op_right
    elif op == ">":
        op_left = Int(op_left + '_g_l')
        op_right = Int(op_right + '_g_r')
        return op_left > op_right
    elif op == ">=":
        op_left = Int(op_left + '_ge_l')
        op_right = Int(op_right + '_ge_r')
        return op_left >= op_right
    # normalization
    if op == "!=":
        op_left = Int(op_left + '_e_l')
        op_right = Int(op_right + '_e_r')
        return Not(op_left == op_right)
    elif op == "<":
        op_left = Int(op_left + '_g_r')
        op_right = Int(op_right + '_g_l')
        return op_left < op_right
    elif op == ">=":
        op_left = Int(op_left + '_ge_r')
        op_right = Int(op_right + '_ge_l')
        return op_left <= op_right
    elif op == '&&':        
        op_left = normalize_operand(op_left)
        op_right = normalize_operand(op_right)
        return And(op_left, op_right)
    elif op == '||':        
        op_left = normalize_operand(op_left)
        op_right = normalize_operand(op_right)
        return Or(op_left, op_right)
    else:
        print 'can not deal with op: %s, op_left: %s, op_right: %s' %(op, op_left, op_right)

"""
@ param operand, p
@ return p == null
@ involve p normalized to p == null
"""
def normalize_operand(operand):
    # p to p == null
    if isinstance(operand, str):
        normalized_operand = get_infix_for_binary_operator('==', operand, my_constant.JOERN_NULL)
    else:
        normalized_operand = operand
    return normalized_operand

"""
@ param two operands
@ return sorted operands
@ involve sort two operands
"""
def order_operands(operand_left, operand_right):
    temp_list = [operand_left, operand_right]
    temp_list.sort()
    return temp_list[0], temp_list[1]

"""
@ param two stmt
@ return sat or unsat
@ involve call z3 to compare two statement
"""
def judge_equality(stmt_one, stmt_two):
    s = Solver()
    s.push()
    int_a, int_b = Bools('int int')
    func_a, func_b = Bools('func func')
    null_a, null_b = Bools('null null')
    stmt_one = Or(And(int_a, func_a), null_a)
    stmt_two = And(Or(int_b, null_b), Or(func_b, null_b))

    # decide whether two statement is equal
    s.add( Xor(stmt_one, stmt_two) )
    s.pop()
    s.push()

    int_a, int_b = Bools('int int')
    s.add(int_a == int_b)
    status = s.check()
    print status
    if status.r == 1:
        print s.model()
    else:
        print "stmt one <=> stmt two"
    s.pop()

if __name__ == "__main__":
    
    print(get_infix_for_postfix(['int', 'int', '==', 'UnaryOp', 'func_ret', '!', '&&']))  
 

    
