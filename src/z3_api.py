import re
from z3 import *
import my_constant

class Z3_api:

    smt_solver = None

    """
    @ param postfix_expr(List)
    @ return infix expression
    @ involve transform postfix(list) expression into infix one(input for z3)
    """
    def judge_equality_for_statments(self, statement_one, statement_two):
        is_equal = True
        if statement_one == statement_two:
            return is_equal
        else:
            if Z3_api.smt_solver is None:
                Z3_api.smt_solver = Solver()
            Z3_api.smt_solver.push()
            # if sat then can be different then unequal
            Z3_api.smt_solver.add(Xor(statement_one, statement_two))
            status = Z3_api.smt_solver.check()
            status_r = status.r
            # sat
            if status_r == 1:
                is_equal = False
            # unsat
            elif status_r == -1:
                is_equal = True
            else:
                print 'unknow status %s, r %d' %(status, status_r)
            Z3_api.smt_solver.pop()
            return is_equal

    """
    @ param postfix_expr(List)
    @ return infix expression
    @ involve transform postfix(list) expression into infix one(input for z3)
    """
    def get_infix_for_postfix(self, postfix_expr):
        infix_expr = []
        for token in postfix_expr:
            if token in ['==', '>', '>=', '!=', '<', '<=', '&&', '||']:
                op_right = infix_expr.pop()
                op_left = infix_expr.pop()
                result = self.__get_infix_for_binary_operator(token, op_left, op_right)
                infix_expr.append(result)
            elif token == '!':
                op = infix_expr.pop()
                result = self.__get_infix_for_unary_operator(op)
                infix_expr.append(result)
            elif token != my_constant.JOERN_UNARY_OPERATOR:
                infix_expr.append(token)
        # check result[postfix without operator]
        if len(infix_expr) == 0:
            return None
        else:
            return self.__normalize_operand(infix_expr[0])

    """
    @ param operand
    @ return infix expression
    @ involve deal with !, Not(op)
    """
    def __get_infix_for_unary_operator(self, operand):
        # !p normalized to Not(p == null)
        operand = self.__normalize_operand(operand)
        return Not(operand)

    """
    @ param operand left and right
    @ return infix expression
    @ involve deal with binary operator (==, >, >=) (&&, or)
    """
    def __get_infix_for_binary_operator(self, op, op_left, op_right):

        if op == "==":
            # normalization == operands order
            op_left, op_right = self.__order_operands(op_left, op_right)
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
        elif op == "<=":
            op_left = Int(op_left + '_ge_r')
            op_right = Int(op_right + '_ge_l')
            return op_left <= op_right
        elif op == '&&':        
            op_left = self.__normalize_operand(op_left)
            op_right = self.__normalize_operand(op_right)
            return And(op_left, op_right)
        elif op == '||':        
            op_left = self.__normalize_operand(op_left)
            op_right = self.__normalize_operand(op_right)
            return Or(op_left, op_right)
        else:
            print 'can not deal with op: %s, op_left: %s, op_right: %s' %(op, op_left, op_right)

    """
    @ param operand, p
    @ return p == null
    @ involve p normalized to p == null
    """
    def __normalize_operand(self, operand):
        # p to p == null
        if isinstance(operand, unicode) or isinstance(operand, str):
            normalized_operand = Not(self.__get_infix_for_binary_operator('==', operand, my_constant.JOERN_NULL))
        else:
            normalized_operand = operand
        return normalized_operand

    """
    @ param two operands
    @ return sorted operands
    @ involve sort two operands
    """
    def __order_operands(self, operand_left, operand_right):
        temp_list = [operand_left, operand_right]
        temp_list.sort()
        return temp_list[0], temp_list[1]

   

if __name__ == "__main__":
    z3_api = Z3_api()
    print(z3_api.get_infix_for_postfix(['int', 'int', '==', 'UnaryOp', 'func_ret', '!', '&&']))  
 

    
