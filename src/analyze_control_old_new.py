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
@ param  is delete log or not, old and new location and filename in file, joern instance of the python-joern api
@ return log, cdg_list, neighbor_list, context_lists, ddg_node, ddg_lists
@ callee cdgNodeAnalysis
@ caller main ..
@ involve retrieve ast of dependency node, include data dependence and control dependence
"""
def getDependendedAstOfLog(change_type, old_loc, old_fileName, new_loc, new_fileName, joern_instance):

    # initialize log, cfg_list, ddg_list
    old_loc = old_loc + ":"
    new_loc = new_loc + ":"
    # query for log statement
    base_query = '_().getLogByFileAndLoc("' + old_fileName + '","' + old_loc + '")'
    old_log_result = joern_instance.runGremlinQuery(base_query)[0]
    base_query = '_().getLogByFileAndLoc("' + new_fileName + '","' + new_loc + '")'
    new_log_result = joern_instance.runGremlinQuery(base_query)[0]

    old_context_list = []
    new_context_list = []
    ddg_list = []
    static_list = []
    old_log = []
    new_log = []
    old_log_id = -1
    new_log_id = -1
    # context length
    contxt_len = 3
    order = str(contxt_len)

    # get old context_list
    if old_log_result:
        old_log = nodeAnalysis(old_log_result)[0]
        old_log_id = old_log[0]
        old_context_list = myUtil.getContext(old_log_id, joern_instance)

     # get new context_list
    if new_log_result:
        new_log = nodeAnalysis(new_log_result)[0]
        new_log_id = new_log[0]
        new_context_list = myUtil.getContext(new_log_id, joern_instance)


    # get ddg list and static list (-: old, + new)
    if change_type == '-':
        log_id = old_log_id
        log = old_log
    else:
        log_id = new_log_id
        log = new_log
    if log_id != -1:
        ddg_list, static_list = myUtil.getDDGAndContent(log_id, joern_instance)

    return log, old_context_list, new_context_list, ddg_list, static_list

"""
@ param  record of fetch_reader line, change_type, 
@ return edited record array, has edited flag(log)
@ caller analyze_old_new
@ callee getDependendedAstOfLog
@ involve retrieve old and new contexts of log statements and store it
"""
def analyze_record( joern_instance, record, change_type):

    old_loc = record[myUtil.FETCH_OLD_LOC]
    new_loc = record[myUtil.FETCH_NEW_LOC]
    old_fileName = record[myUtil.FETCH_OLD_FILE]
    new_fileName = record[myUtil.FETCH_NEW_FILE]

    # query database with loc and filename
    log, old_context_list, new_context_list, \
        ddg_lists, static_lists = getDependendedAstOfLog(change_type, old_loc, old_fileName, new_loc, new_fileName, joern_instance)

    # record the info: log node
    record[myUtil.FETCH_LOG] = json.dumps(log)
    # cdg ndoe, neighbor node, context_lists
    record.append(json.dumps(old_context_list))
    record.append(json.dumps(new_context_list))
    # ddg node, ddg lists
    record.append(json.dumps(ddg_lists))
    record.append(json.dumps(static_lists))

    return record, log

"""
@ param ...
@ return nothing
@ caller main
@ callee analyze_record
@ involve operate fetch and analyze files
"""
def analyze_old_new():

    fetch = file(myUtil.FETCH_FILE_NAME, 'rb')
    # initialize write file
    analysis = file(myUtil.ANALYZE_OLD_NEW_FILE_NAME, 'wb')
    analyze_writer = csv.writer(analysis)
    analyze_writer.writerow(myUtil.ANALYZE_OLD_NEW_TITLE)
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
        if count % 10 == 0:
            print "now record the No. %d analyze" %count
        # call deal_line to retrieve location info(- included)
        record, log = analyze_record(joern_instance, record, record[myUtil.FETCH_CHANGE_TYPE])

        # update analyze data is has edited
        if log:
            # record.pop(0)
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

    analyze_old_new()
