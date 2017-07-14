from joern.all import JoernSteps

"""
@ param  result list
@ return list of analyzed node info
@ callee ...
@ caller getDependendedAstOfLog ..
@ analyze query node. include : id, isCFGNode, type, code
"""
def nodeAnalysis(result):

    cfg_list = []
    for record in result:
        value_list = []
        value_list.append(str(record._id))
        value_list.append(record.properties['isCFGNode'])
        value_list.append(record.properties['type'])
        value_list.append(record.properties['code'])
        cfg_list.append(value_list)

    return cfg_list

"""
@ param  filename and location in file, joern instance of the python-joern api
@ return node list (type and code)
@ callee cdgNodeAnalysis
@ caller main ..
@ involve retrieve ast of dependency node, include data dependence and control dependence
"""
def getDependendedAstOfLog(filename, location, joern_instance):

    # initialize log, cfg_list, ddg_list
    log = []
    cdg_list = []
    ddg_list = []

    location = location + ":"
    # query for log statement
    base_query = '_().getLogByFileAndLoc("' + filename + '","' + location + '")'
    log_result = joern_instance.runGremlinQuery(base_query)[0]
    # if no log node found return null
    cond_lists = []
    if log_result:

        # analysis query result (id, isCFGNode, type, code)
        log = nodeAnalysis(log_result)[0]

        order = '5'
        # condition node list (control type, id, isCFGNode, type, code)
        label_query = 'g.V[36].getCondition()'
        label_list = joern_instance.runGremlinQuery(label_query)[0]
        cdg_query = '_().getCFGControlByLog(' + log[0] + ',' + order +')'
        cdg_list = joern_instance.runGremlinQuery(cdg_query)[0]

        # deal with each condition
        for condition in cdg_list:
            # get type
            is_true = condition[0]

            # get condition node
            cond_node = condition[1]
            cond_id = str(cond_node[0])

            # get condition variable map(variable name, variable type)
            var_query = '_().getVarMap(' + cond_id +')'
            cond_var_map = joern_instance.runGremlinQuery(var_query)[0]
            # make dictionary based on query result
            var_dict = {}
            for var_map in cond_var_map:
                var_dict[var_map[0]] = var_map[1]

            # get condition list of this condition
            # cond_list = joern_instance.runGremlinQuery('g.V[30].getCondition()')[0]
            cond_query = '_().getConditionListByid(' + cond_id + ')'
            cond_list = joern_instance.runGremlinQuery(cond_query)[0]
            for cond in cond_list:
                for var in cond:
                    # update var to type if find in dictionary
                    if var_dict.has_key(var):
                        cond[cond.index(var)] = var_dict[var]
                # add type condition into conditin lists of log statement
                cond_lists.append([cond, is_true])

    return cond_lists


# initialization
joern_instance = JoernSteps()
joern_instance.addStepsDir("/opt/joern-code/query/")
joern_instance.setGraphDbURL("http://localhost:7474/db/data/")

# connect to database
joern_instance.connectToDatabase()

loc = '17'
filename = 'mytest.c'

getDependendedAstOfLog(filename, loc, joern_instance);
