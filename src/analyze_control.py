#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import base64
import json
import myUtil
from itertools import islice
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
@ param  ddg_node[ddg, variable], ddg_lists and joern instance of the python-joern api
@ return ddg_lists
@ callee ...
@ caller getDependendedAstOfLog ..
@ involve get ddg list by changing variables into type and callee into function name ...  
"""
def getDDGList(ddg_node, ddg_lists, joern_instance):
    # get type
    if not ddg_node:
        return ddg_lists

    # get statement and variable
    ddg = ddg_node[1]
    ddg_id = str(ddg[0])
    variable = ddg_node[0]

    # get use variable map(variable name, variable type)
    var_query = '_().getVarMap(' + ddg_id +')'
    ddg_var_map = joern_instance.runGremlinQuery(var_query)[0]
    # make dictionary based on query result
    var_dict = {}
    for var_map in ddg_var_map:
        var_dict[var_map[0]] = var_map[1]
    # get def variable map(variable name, variable type)
    var_query = '_().getVarMapForDDG(' + ddg_id +')'
    ddg_var_map = joern_instance.runGremlinQuery(var_query)[0]
    # append dictionary
    for var_map in ddg_var_map:
        var_dict[var_map[0]] = var_map[1]


    # get statement list(postfix)
    ddg_query = '_().getCFGStatementLists(' + ddg_id + ')'
    ddg_list = joern_instance.runGremlinQuery(ddg_query)[0]

    # update ddg list to typed ddg list
    for var in ddg_list:
        if var is None:
            continue
        # update var to type if find in dictionary
        if var_dict.has_key(var):
            ddg_list[ddg_list.index(var)] = var_dict[var]
            continue
        # remove namespace before::
        var = myUtil.removeNamespace(var)

    # update variable to variable type
    variable = var_dict.get(variable, variable)
    # add type ddg into ddg lists of log statement
    # context_lists.append([cond, control_label])
    ddg_lists.append([ddg_list, variable])

    return ddg_lists

"""
@ param  neighbor,  context_lists and joern instance of the python-joern api
@ return context_lists
@ callee ...
@ caller getDependendedAstOfLog ..
@ involve get neighbor list by changing variables into type and callee into function name ...  
"""
def getNeighborList(neighbor, context_lists, joern_instance):

    # get type
    if not neighbor:
        return context_lists

    control_label = ""

    # get neighbor node
    neighbor_node = neighbor[1]
    neighbor_id = str(neighbor_node[0])


    # get use variable map(variable name, variable type)
    var_query = '_().getVarMap(' + neighbor_id +')'
    neighbor_var_map = joern_instance.runGremlinQuery(var_query)[0]
    # make dictionary based on query result
    var_dict = {}
    for var_map in neighbor_var_map:
        var_dict[var_map[0]] = var_map[1]
    # get def variable map(variable name, variable type)
    var_query = '_().getVarMapForDDG(' + neighbor_id +')'
    neighbor_var_map = joern_instance.runGremlinQuery(var_query)[0]
    # append dictionary
    for var_map in neighbor_var_map:
        var_dict[var_map[0]] = var_map[1]

    # get neighbor statement(postfix)
    neighbor_query = '_().getCFGStatementLists(' + neighbor_id + ')'
    neighbor_list = joern_instance.runGremlinQuery(neighbor_query)[0]

    # update neighbor list to typed neighbor list
    for var in neighbor_list:
        if var is None:
            continue
        # update var to type if find in dictionary
        if var_dict.has_key(var):
            neighbor_list[neighbor_list.index(var)] = var_dict[var]
            continue
        # remove namespace before::
        var = myUtil.removeNamespace(var)


    # add type neighbor into context lists of log statement
    # context_lists.append([cond, control_label])
    context_lists.append([neighbor_list])

    return context_lists # cond + control_label


"""
@ param  condition, context_lists and joern instance of the python-joern api
@ return context_lists
@ callee ...
@ caller getDependendedAstOfLog ..
@ involve get condition list by changing variables into type and callee into function name ...  
"""
def getCondList(condition, context_lists, joern_instance):

    # get type
    if not condition:
        return context_lists

    if not condition[0]:
        control_label = ''
    else:
        control_label = condition[0]

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

    cond_query = '_().getConditionListByid(' + cond_id + ')'
    cond_list = joern_instance.runGremlinQuery(cond_query)[0] # just one cond
    # get cond_list of this condition
    is_case = control_label.startswith("case")
    if is_case:
        # switch case
        cond_list[0].append(control_label[4:].strip())
        cond_list[0].append('==')

    # update condition list to typed condition list
    for cond in cond_list:
        for var in cond:
            if var is None:
                continue
            # update var to type if find in dictionary
            if var_dict.has_key(var):
                cond[cond.index(var)] = var_dict[var]
                continue
            # remove namespace before::
            var = myUtil.removeNamespace(var)

        # add type condition into conditin lists of log statement
        # context_lists.append([cond, control_label])
        context_lists.append([cond])

    return context_lists # cond + control_label


"""
@ param  filename and location in file, joern instance of the python-joern api
@ return log, cdg_list, neighbor_list, context_lists, ddg_node, ddg_lists
@ callee cdgNodeAnalysis
@ caller main ..
@ involve retrieve ast of dependency node, include data dependence and control dependence
"""
def getDependendedAstOfLog(filename, location, joern_instance):

    # context length
    contxt_len = 5

    # initialize log, cfg_list, ddg_list
    log = []
    cdg_list = []
    neighbor_list = []
    context_lists = []
    ddg_nodes = []
    ddg_lists = []
    static_lists = []
    location = location + ":"
    order = str(contxt_len)
    # query for log statement
    base_query = '_().getLogByFileAndLoc("' + filename + '","' + location + '")'
    log_result = joern_instance.runGremlinQuery(base_query)[0]


    if log_result:

        # analysis query result (id, isCFGNode, type, code)
        log = nodeAnalysis(log_result)[0]

        # condition node list (control type, id, isCFGNode, type, code)
        cdg_query = '_().getCFGControlByLog(' + log[0] + ',' + order +')'
        cdg_list = joern_instance.runGremlinQuery(cdg_query)[0] # true/false + cond_node
        # deal with each condition
        for condition in cdg_list:
            context_lists = getCondList(condition, context_lists, joern_instance)

        # add flowlabel to make sure the total context count is at least 5
        # context = control + neighbor
        if len(cdg_list) < contxt_len:
            neighbor_query = '_().getCFGStatementByLog(' + log[0] + ',' + order +')'
            neighbor_list = joern_instance.runGremlinQuery(neighbor_query)[0] #  + cond_node
        # deal with each neighbor
        for neighbor in neighbor_list:
            context_lists = getNeighborList(neighbor, context_lists, joern_instance)

        # get ddg node and ddg lists
        ddg_query = '_().getDDG(' + log[0] + ')'
        ddg_nodes = joern_instance.runGremlinQuery(ddg_query)[0]
        # deal with each ddg_node to get ddg_lists
        for ddg_node in ddg_nodes:
            ddg_lists = getDDGList(ddg_node, ddg_lists, joern_instance)

        # get static string
        static_query = '_().getStaticStr(' + log[0] + ')'
        static_lists = joern_instance.runGremlinQuery(static_query)[0]


    return log, cdg_list, neighbor_list, context_lists, ddg_nodes, ddg_lists, static_lists

"""
@ param  record of fetch_reader line, index of log, index of log_loc, index of store_name
@ return edited record array, has edited flag(log)
@ caller analyze
@ callee getDependendedAstOfLog
@ involve retrieve context info through joern database
"""
def analyze_record( joern_instance, record, log_index, loc_index, file_index):

    loc = record[loc_index]
    filename = record[file_index]

    # query database with loc and filename
    log, cdg_list, neighbor_list, context_lists, \
        ddg_nodes, ddg_lists, static_lists = getDependendedAstOfLog(filename, loc, joern_instance)

    # record the info: log node
    record[log_index] = json.dumps(log)
    # cdg ndoe, neighbor node, context_lists
    record[loc_index] = json.dumps(cdg_list)
    record[6] = json.dumps(neighbor_list)
    record[7] = json.dumps(context_lists)
    # ddg node, ddg lists
    record.append(ddg_nodes)
    record.append(ddg_lists)
    record.append(static_lists)
    # record store Name and log location
    record.append(filename)
    record.append(loc)

    return record, log

"""
@ param  user and repos
@ return nothing
@ caller main
@ callee analyze_record
@ involve operate fetch and analyze files
"""
def analyze(user, repos):

    fetch = file('data/fetch_' + user + '_' + repos + '.csv', 'rb')
    # initialize write file
    analysis = file('data/analyz_joern_' + user + '_' + repos + '.csv', 'wb')
    analyze_writer = csv.writer(analysis)
    analyze_writer.writerow(['commit_message', 'file_name', 'change_type',\
            'log_node', 'cdg_nodes', 'neighbor_nodes','context_lists', 'ddg_nodes', 'ddg_lists', 'static_lists', 'store_name', 'log_loc'])
    # initialize read file
    records = csv.reader(fetch)
    # initialize python-joern instance
    joern_instance = JoernSteps()
    joern_instance.addStepsDir("/data/joern-code/query/")
    joern_instance.setGraphDbURL("http://localhost:7474/db/data/")
    # connect to database
    joern_instance.connectToDatabase()

    # traverse the fetch csv file to update context info
    count = 0
    # remove the table title
    for record in islice(records, 1, None):
        # default + type and use new file
        file_index = 7
        # use old file for - type
        if record[3] == '-':
            file_index = 6
        if count % 10 == 0:
            print "now record the No. %d analyze" %count
        # call deal_line to retrieve location info(- included)
        record, log = analyze_record(joern_instance, record, 4, 5, file_index)

        # update analyze data is has edited
        if log:
            record.pop(0)
            # record.pop(6)
            analyze_writer.writerow(record)
            count = count + 1

    # close files
    analysis.close()
    fetch.close()


"""
main function
"""
if __name__ == "__main__":
    # several configuration constant: user, repos
    # user = 'mongodb'
    # repos = 'mongo'
    # user = 'opencv'
    # repos = 'opencv'
    user = 'apple'
    repos = 'swift'
    # user = 'llvm-mirror'
    # repos = 'clang'
    # user = 'torvalds'
    # repos = 'linux'

    analyze( user, repos)
