#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import base64
import json
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
@ param  condition, var map, cond_lists and joern instance of the python-joern api
@ return cond_lists
@ callee ...
@ caller getDependendedAstOfLog ..
@ involve retrieve 
"""
def getCondList(condition, cond_lists, joern_instance):

    # get type
    if not condition:
        return cond_lists

    if not condition[0] or len(condition[0]) > 1:
        control_label = ''
    else:
        control_label = condition[0][0]

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

    # get cond_list of this condition
    is_case = control_label.startswith("case")
    if is_case:
        # switch case
        cond_query = '_().getConditionListByidSwitch(' + cond_id + ')'
        cond_list = joern_instance.runGremlinQuery(cond_query) # just one cond
        cond_list[0].append(control_label[4:].strip())
        cond_list[0].append('==')
        control_label = None
    else:
        # if condition
        cond_query = '_().getConditionListByid(' + cond_id + ')'
        cond_list = joern_instance.runGremlinQuery(cond_query)[0]

    # update condition list to typed condition list
    for cond in cond_list:
        for var in cond:
            # update var to type if find in dictionary
            if var_dict.has_key(var):
                cond[cond.index(var)] = var_dict[var]

        # add type condition into conditin lists of log statement
        cond_lists.append([cond, control_label])

    return cond_lists # cond + control_label


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
    cond_lists = []
    location = location + ":"
    order = '5'
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
            cond_lists = getCondList(condition, cond_lists, joern_instance)

    return log, cdg_list, cond_lists # cond + true/false

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
    log, cdg_list, cond_lists = getDependendedAstOfLog(filename, loc, joern_instance)

    # record the info
    record[log_index] = json.dumps(log)
    record[loc_index] = json.dumps(cdg_list)
    # no.6 column
    record[6] = json.dumps(cond_lists)

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
                         'log_node', 'cdg_nodes', 'condition_lists'])
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
            record.pop(6)
            analyze_writer.writerow(record)
            count = count + 1

    # close files
    analysis.close()
    fetch.close()


"""
main function
"""

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
