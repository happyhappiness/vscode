import re
from joern.all import JoernSteps
from py2neo.packages.httpstream import http
import my_constant

class Joern_api:
    joern_instance = None

    def __init__(self):
        # initialization
        if Joern_api.joern_instance is None:
            # initialization joern
            Joern_api.joern_instance = JoernSteps()
            Joern_api.joern_instance.addStepsDir("/usr/info/code/cpp/LogMonitor/LogMonitor/second/joern-code/query/")
            Joern_api.joern_instance.setGraphDbURL("http://localhost:7474/db/data/")
            # connect to database
            Joern_api.joern_instance.connectToDatabase()

        self.log = None
        self.log_id = None
        self.order = '2'
        self.flow_order = '30'

        self.log_depended_var = None
        self.argument = None
        self.var_type_dict = {}

    """
    @ param depth int
    @ return
    @ involve update control dependece query order(depth)
    """
    def set_order(self, order):
        self.order = str(order)

    """
    @ param
    @ return [condition id + flag], normalized condition info
    @ involve get condition and controled statements and its condition info
    """
    def get_all_condition(self):
        # set time out
        # http.socket_timeout = 9999
        conditions_query = '_().getAllConditions()'
        conditions = Joern_api.joern_instance.runGremlinQuery(conditions_query)
        condition_list = []
        if conditions is not None:
            print 'conditions size: %d' %(len(conditions))
            index = 0
            for condition in conditions:
                condition_id = str(condition)
                node_id, loc, file_name = self.__get_controled_node_for_condition(condition_id)
                if node_id is None:
                    continue
                # get condition and normalized condition for each node
                condition_info = self.__get_control_dependence_for_node(node_id)
                normalized_condition = []
                for condition in condition_info:
                    node_std_code = self.__get_std_condition(condition[0], condition[1])
                    if len(normalized_condition) == 0:
                        normalized_condition = node_std_code
                    else:
                        normalized_condition = node_std_code + normalized_condition + ['&&']
                # append this condition info to condition_list
                condition_list.append([file_name, loc, condition_info, normalized_condition])
                if index % 10 == 0:
                    print 'now processing condition %d' %(index)
                index += 1
        return condition_list
     
    """
    @ param condition_id
    @ return node_id, location and file
    @ involve get controled node info for given condition node
    """
    def __get_controled_node_for_condition(self, condition_id):
        node_query = '_().getControledNodeForCondition(' + condition_id + ')'
        node = Joern_api.joern_instance.runGremlinQuery(node_query)
        node_id = loc = file_name = None
        if node is not None and len(node) != 0:
            node = node[my_constant.JOERN_DEFALUT]
            node_id = str(node[0][my_constant.JOERN_ID])
            loc = node[0][my_constant.JOERN_LOCATION]
            # if loc is None:
            #     print "condition id is %s, node id is %s" %(condition_id, node_id)
            loc = loc[0:loc.index(':')]
            file_name = node[1]
        return node_id, loc, file_name
    """
    @ param node_id
    @ return [condition id + flag], normalized condition info
    @ involve get condition for node
    """
    def __get_control_dependence_for_node(self, node_id):
        cdg_query = '_().getControlDependence(' + node_id + ',' + self.order +')'
        cdg_list = Joern_api.joern_instance.runGremlinQuery(cdg_query)
        condition_info = []
        if cdg_list is not None and len(cdg_list) != 0:
            cdg_list = cdg_list[my_constant.JOERN_DEFALUT]
            # node_id, statement, label
            for condition in cdg_list:
                control_node_id = str(condition[my_constant.JOERN_ID])
                label = self.__get_label_for_control(node_id, control_node_id)
                condition_info.append((control_node_id, label))
        return condition_info

    """
    @ param file name and log location(from 0, int)
    @ return log statement
    @ involve query log node of given file in given location
    """
    def set_log(self, file_name, log_loc):
        log_loc = str(log_loc + 1) + ':'
        base_query = '_().getLogByFileAndLoc("' + file_name + '","' + log_loc + '")'
        log_result = Joern_api.joern_instance.runGremlinQuery(base_query)
        if log_result is not None and len(log_result) != 0:
            log_result = log_result[my_constant.JOERN_DEFALUT]
            if len(log_result) != 0:
                log_result = log_result[my_constant.JOERN_DEFALUT]
                self.log_id = str(log_result[my_constant.JOERN_ID])
                # self.log = log_result[my_constant.JOERN_CODE]
                return True
        return False

    """
    @ param
    @ return data dependence of given log node
    @ involve get control statement and identified variable type
    """
    def get_control_dependence(self):
        return self.__get_control_dependence_for_node(self.log_id)

    """
    @ param
    @ return data dependence of given log node
    @ involve get control statement and identified variable type
    """
    def get_control_dependence_for_patch(self):
        condition_info = self.__get_control_dependence_for_node(self.log_id)
        normalized_condition = []
        for condition in condition_info:
            node_std_code = self.__get_std_condition(condition[0], condition[1])
            if len(normalized_condition) == 0:
                normalized_condition = node_std_code
            else:
                normalized_condition = node_std_code + normalized_condition + ['&&']
        return normalized_condition
        


    """
    @ param condition node id and condition label(true or false)
    @ return normalized condition(type and post prefix expression)
    @ involve identify var type and remove ()
    """
    def __get_std_condition(self, condition_id, condition_label):
        std_condition = []
        # sub expression type normalization
        depended_var = self.__get_depended_var_for_statement(condition_id)
        sub_expressions = self.__get_sub_expression(condition_id)
        for expression in sub_expressions:
            var_type = self.__get_var_type_for_node(expression, depended_var)
            if var_type is None:
                var_type = my_constant.JOERN_UNKNOWN
            if var_type != my_constant.JOERN_UNARY_OPERATOR:
                std_condition.append(var_type)
        # condition structure normalization
        if condition_label == 'False':
            std_condition.append('!')
        return std_condition

    """
    @ param
    @ return argument types of log
    @ involve identify argument type log statement
             S1: function; S2: constant; S3:data dependence;
    """
    def get_argument_type(self):
        # get arg type from dependence relation
        self.argument = []
        depended_var = self.__get_depended_var_for_statement(self.log_id)
        arguments = self.__get_argument()
        for arg in arguments:
            var_type = self.__get_var_type_for_node(arg, depended_var)
            if var_type is None:
                var_type = my_constant.JOERN_UNKNOWN
            if var_type != my_constant.JOERN_UNARY_OPERATOR:
                self.argument.append(var_type)
        # print self.argument
        return self.argument

    """
    @ param
    @ return data dependence of given log node
    @ involve identify variable type for log statement by data dependence
    """
    def __get_depended_var_for_statement(self, node_id):
        # get argument type is can be found
        depended_var = {}
        data_dependence = \
            self.__get_data_dependence_for_node(node_id)
        for data in data_dependence:
            node_id = data[0]
            node_type = data[2]
            var = data[3]
            var_type = self.__get_var_type_for_statment(node_id, node_type, var, 0)
            if not depended_var.has_key(var) or self.__get_priority_for_type(var_type) > self.__get_priority_for_type(depended_var[var]):
                depended_var[var] = var_type     
        return depended_var

    """
    @ param var type
    @ return its priority
    @ involve func > certain > member > null > unknown/none
    """
    def __get_priority_for_type(self, var_type):
        if var_type is None:
            order = 0
        elif var_type == my_constant.JOERN_NULL:
            order = 1
        elif var_type == my_constant.JOERN_MEMEBER:
            order = 2
        elif var_type.endswith(my_constant.JOERN_CALLEE_FLAG):
            order = 4
        else:
            order = 3
        return order
        
    """
    @ param condition node id
    @ return sub expressions
    @ involve nodes 1 level deeper than RelationalExpression and UnaryOp
    """
    def __get_sub_expression(self, condition_id):
        sub_expressions_query = '_().getSubExpressions(' + condition_id + ')'
        sub_expressions = Joern_api.joern_instance.runGremlinQuery(sub_expressions_query)
        if sub_expressions is not None:
            for i in range(len(sub_expressions)):
                sub_expressions[i] = sub_expressions[i][my_constant.JOERN_DEFALUT]
            return sub_expressions
    """
    @ param
    @ return arguments of log node
    @ involve query argument of log function
    """
    def __get_argument(self):
        argument_query = '_().getArguments(' + self.log_id + ')'
        arguments = Joern_api.joern_instance.runGremlinQuery(argument_query)
        if arguments is not None:
            for i in range(len(arguments)):
                arguments[i] = arguments[i][my_constant.JOERN_DEFALUT]
            return arguments

    """
    @ param node info[id, code, type]
    @ return var type
    @ involve identify var type based self and children
    """
    def __get_var_type_for_node(self, node, depended_var_dict):
        node_id = str(node[my_constant.JOERN_ID])
        var_type = self.__get_var_type_for_operation(node, depended_var_dict)
        if var_type is None:
            var_type = self.__get_var_type_for_children(node_id, depended_var_dict)
        
        return var_type

    """
    @ param node info[id, code, type]
    @ return var type
    @ involve identify var type based on node type(bool, memeber, constants, func, variable)
    """
    def __get_var_type_for_operation(self, node, depended_var_dict):
        node_code = node[my_constant.JOERN_CODE]
        node_type = node[my_constant.JOERN_TYPE]
        var_type = self.__get_var_type_for_node_except_identifier(node)
        if var_type is None and node_type == 'Identifier':
            var_type = self.__get_var_type_for_variable(node_code, depended_var_dict)

        return var_type


    """
    @ param node id
    @ return node type
    @ involve get children of argument and deal with each operation
    """
    def __get_var_type_for_children(self, node_id, depended_var):
        var_type = None
        # get right children
        operations_query = '_().getOperations(' + node_id + ')'
        operations = Joern_api.joern_instance.runGremlinQuery(operations_query)
        if operations is not None:
            for operation in operations:
                var_type = self.__get_var_type_for_operation(operation[my_constant.JOERN_DEFALUT], depended_var)
                if var_type is not None and not var_type.endswith(my_constant.JOERN_CALLEE_FLAG):
                    break
        return var_type

    """
    @ param id, type and var of node
    @ return queried var type
    @ involve S1: dict; S2: decl type; S3:right value; S4:depended node
    """
    def __get_var_type_for_statment(self, node_id, node_type, var, depth):
        if depth > int(self.order):
            return None
        var_type = self.__get_var_type_with_dict(node_id)
        # no node info in var_type_dict
        if var_type is None:
            # get type if type is parameter or declaration
            var_type = self.__get_var_type_with_statemtnt_type(node_id, node_type)
            if var_type is None:
                # get type if right value is decidable(call, bool, member, primary)
                var_type = self.__get_var_type_with_right_value(node_id)
                if var_type is None:
                    # get type from depended node
                    depended_nodes = self.__get_data_dependence_for_node(node_id)
                    depth += 1
                    for node in depended_nodes:
                        var_type = self.__get_var_type_for_statment(node[0], node[2], node[3], depth)
                        if var_type is not None:
                            break
            # update var type dict if found(may be None)
            self.var_type_dict[node_id] = [var_type, var]

        return var_type

    """
    @ param id of node
    @ return queried var type
    @ involve query dict with node_id
    """
    def __get_var_type_with_dict(self, node_id):
        var_type = None
        # get type
        if self.var_type_dict.has_key(node_id):
            var_type = self.var_type_dict[node_id][0]

        return var_type

    """
    @ param id and type of node
    @ return var type
    @ involve deal with Parameter and IdentifierDeclStatement
    """
    def __get_var_type_with_statemtnt_type(self, node_id, node_type):
        var_type = None
        # get type
        if node_type == 'Parameter' or node_type == 'IdentifierDeclStatement':
            type_query = '_().getVarTypeForParaOrDecl(' + node_id + ')'
            var_type_result = Joern_api.joern_instance.runGremlinQuery(type_query)
            if var_type_result is not None and len(var_type_result) != 0:
                var_type = var_type_result[my_constant.JOERN_DEFALUT]
                # array type to pointer
                if var_type.find('[') != -1:
                    var_type = re.sub(r'\[(.|\n)*\]', '*', var_type)

        return var_type

    """
    @ param id of node
    @ return var type
    @ involve deal with right value type
    """
    def __get_var_type_with_right_value(self, node_id):
        var_type = None
        # get right value
        right_value_query = '_().getRightValue(' + node_id + ')'
        right_value = Joern_api.joern_instance.runGremlinQuery(right_value_query)
        if right_value is not None and len(right_value) != 0:
            right_value = right_value[my_constant.JOERN_DEFALUT]
            if len(right_value) != 0:
                var_type = self.__get_var_type_for_right_value(right_value[my_constant.JOERN_DEFALUT])

        return var_type

    """
    @ param node info[id, code, type(,operator)]
    @ return var type
    @ involve identify var type based on self except identifier or children
    """
    def __get_var_type_for_right_value(self, node):
        node_id = str(node[my_constant.JOERN_ID])
        var_type = self.__get_var_type_for_node_except_identifier(node)
        if var_type is None:
            var_type = self.__get_var_type_for_right_value_children(node_id)

        return var_type

    """
    @ param node info[id, code, type(,operator)]
    @ return var type
    @ involve identify var type based on children operations except identifier
    """
    def __get_var_type_for_right_value_children(self, node_id):
        # get sub operation
        var_type = None
        # get right children
        operations_query = '_().getOperations(' + node_id + ')'
        operations = Joern_api.joern_instance.runGremlinQuery(operations_query)
        if operations is not None:
            for operation in operations:
                var_type = self.__get_var_type_for_node_except_identifier(operation[my_constant.JOERN_DEFALUT])
                if var_type is not None and not var_type.endswith(my_constant.JOERN_CALLEE_FLAG):
                    break
        return var_type

    """
    @ param node info[id, code, type(,operator)]
    @ return var type
    @ involve identify var type based on func, bool, memeber, constants
    """
    def __get_var_type_for_node_except_identifier(self, node):        
        node_id = str(node[my_constant.JOERN_ID])
        node_code = node[my_constant.JOERN_CODE]
        node_type = node[my_constant.JOERN_TYPE]
        var_type = None
        # bool operator
        if node_type in my_constant.JOERN_BOOL_OPERATOR:
            if len(node) > my_constant.JOERN_OPERATOR:
                var_type = node[my_constant.JOERN_OPERATOR]
            else:
                var_type = my_constant.JOERN_BOOL
        elif node_type == my_constant.JOERN_UNARY_OPERATOR:
            if node_code[0] == '!':
                if len(node) == my_constant.JOERN_OPERATOR:
                    var_type = my_constant.JOERN_BOOL
                else:
                    var_type = node_code[0]
            # condition do not need unary operator(already have children) while argument need their children
            elif len(node) > my_constant.JOERN_OPERATOR:
                var_type = my_constant.JOERN_UNARY_OPERATOR
        elif node_type in my_constant.JOERN_ADDRESS_OPERATOR:
            var_type = my_constant.JOERN_MEMEBER
        elif node_type in my_constant.JOERN_BIT_OPERATOR:
            var_type = my_constant.JOERN_BOOL
        elif node_type == 'PrimaryExpression':
            var_type = self.__get_var_type_for_constant(node_code)
        elif node_type == 'CallExpression':
            var_type = self.__get_var_type_with_callee(node_id)
        elif node_type == my_constant.JOERN_ASSIGN_OPERATOR:
            var_type = self.__get_var_type_for_assignment(node_id)
        elif node_type == 'Identifier':
            var_type = self.__get_var_type_for_constant_identifier(node_code)
        return var_type

    """
    @ param id of node
    @ return var type
    @ involve get callee
    """
    def __get_var_type_with_callee(self, node_id):
        var_type = None
        # get right value
        callee_query = '_().getCallee(' + node_id + ')'
        callee = Joern_api.joern_instance.runGremlinQuery(callee_query)
        if callee is not None and len(callee) != 0:
            var_type = callee[my_constant.JOERN_DEFALUT] + my_constant.JOERN_CALLEE_FLAG

        return var_type

    """
    @ param id of node
    @ return var type
    @ involve get callee
    """
    def __get_var_type_for_assignment(self, node_id):
        var_type = None
        # get right value
        right_value_query = '_().getRightValueForAssignment(' + node_id + ')'
        right_value = Joern_api.joern_instance.runGremlinQuery(right_value_query)
        if right_value is not None and len(right_value) != 0:
            right_value = right_value[my_constant.JOERN_DEFALUT]
            if len(right_value) != 0:
                var_type = self.__get_var_type_for_right_value(right_value[my_constant.JOERN_DEFALUT])

        return var_type
    # """
    # @ param id of node
    # @ return var type
    # @ involve deal with primary expression
    # """
    # def __get_var_type_with_constants(self, node_id):
    #     var_type = None
    #     # get right children
    #     constant_query = '_().getPrimaryExpression(' + node_id + ')'
    #     constants = Joern_api.joern_instance.runGremlinQuery(constant_query)
    #     if constants is not None:
    #         for constant in constants:
    #             var_type = self.__get_var_type_for_constant(constant)
    #             if var_type is not None and var_type != 'constant':
    #                 break
    #     return var_type

    # """
    # @ param id of node
    # @ return var type
    # @ involve deal with primary expression
    # """
    # def __get_var_type_with_variables(self, node_id, depended_var_dict):
    #     var_type = None
    #     # get right children
    #     variable_query = '_().getIdentifier(' + node_id + ')'
    #     variables = Joern_api.joern_instance.runGremlinQuery(variable_query)
    #     if variables is not None:
    #         for variable in variables:
    #             var_type = self.__get_var_type_for_variable(variable, depended_var_dict)
    #             if var_type is not None and not var_type.endswith(my_constant.JOERN_CALLEE_FLAG):
    #                 break
    #     return var_type
    """
    @ param identifier code
    @ return var type
    @ involve regrex match to decide variable type(null, macro, None)
    """
    def __get_var_type_for_constant_identifier(self, constant):
        var_type = None
        if re.match(r'^(null)$', constant, re.I):
            var_type = my_constant.JOERN_NULL
        elif re.match(r'^[A-Z0-9_]+$', constant):
            var_type = 'macro'
        return var_type
        
    """
    @ param constant
    @ return var type
    @ involve regrex match to decide variable type
    """
    def __get_var_type_for_constant(self, constant):
        var_type = None
        if re.match(r'^"(.|\n)*"$', constant, re.I | re.M):
            var_type = 'string'
        elif re.match(r'^\'[\\]*\S\'$', constant, re.I):
            var_type = 'char'
        elif re.match(r'^[0-9]+$', constant, re.I):
            if constant == '0':
                var_type = my_constant.JOERN_NULL
            else:
                var_type = 'int'
        else:
            var_type = 'constant'

        return var_type

    """
    @ param variable
    @ return variable type
    @ involve query data dependence dict
    """
    def __get_var_type_for_variable(self, variable, depended_var_dict):
        var_type = None
        if depended_var_dict.has_key(variable):
            var_type = depended_var_dict[variable]
        return var_type

    """
    @ param id of node
    @ return depended nodes
    @ involve get depended nodes of given node [id, code, type, var]
    """
    def __get_data_dependence_for_node(self, node_id):
        ddg_query = '_().getDefDependence(' + node_id + ')'
        ddg_list = Joern_api.joern_instance.runGremlinQuery(ddg_query)
        depended_nodes = []
        if ddg_list is not None:
            # node_id, statement, var
            ddg_list = ddg_list[my_constant.JOERN_DEFALUT]
            for data in ddg_list:
                var = data[0]
                node_id = str(data[1][my_constant.JOERN_ID])
                node_code = data[1][my_constant.JOERN_CODE]
                node_type = data[1][my_constant.JOERN_TYPE]
                depended_nodes.append([node_id, node_code, node_type, var])
        return depended_nodes

    """
    @ param id of control node
    @ return flow label between log node and control node
    @ involve get flowlabel between control and controled node
    """
    def __get_label_for_control(self, node_id, control_node_id):
        label_query = '_().getControlLabel(' + node_id + ',' + control_node_id + ',' + self.flow_order + ')'
        label = Joern_api.joern_instance.runGremlinQuery(label_query)
        if label is not None and len(label) != 0:
            label = label[my_constant.JOERN_DEFALUT]
            if len(label) == 0:
                label = ''
            else:
                label = label[my_constant.JOERN_DEFALUT]
        return label

if __name__ == "__main__":
    filename = 'function_29.cpp'
    joern_api = Joern_api()
    print joern_api.get_all_condition()
    # joern_api.set_log(filename, 65)
    # print joern_api.get_control_dependence()
    # print joern_api.get_argument_type()
    # if re.match(r'^[A-Z0-9_]+$', 'BZ2_bzlibVersion'):
    #     print 'is macro'
    # else:
    #     print 'is not macro'

