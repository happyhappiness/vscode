#-*-coding: utf-8 -*-
import cluster_control
import analyze_control
import myUtil
import csv
import json
import re
from itertools import islice
from joern.all import JoernSteps

"""
@ param ...
@ return log_function
@ caller main
@ callee ...
@ involve retrieve log function name from logging_statement.out
"""
def retrieveLogFunction():
    log_functions = []
    log_statement = open('data/analyze/logging_statement.out', 'rb')
    log_function = file('data/analyze/function' + user + '_' + repos + '.csv', 'wb')
    lines = log_statement.readlines()

    for line in lines:
        log_function = line[0:line.find("@")]
        if not log_function in log_functions:
            log_functions.append(log_function)
    return log_functions

"""
@ param log function name, joern_instance
@ return log info: call file, call location, cdg_list, neighbor_list, ddg_list, static_list, cluster index 
@ caller main
@ callee ...
@ involve retrieve log function name from logging_statement.out
"""
def getLogInfo(log_functions, joern_instance):
    log_call_infos = []
    # get log statement id from log function name
    for log_function in log_functions:
        log_call_query = '_().logToCallStatements("' + log_function +'")'
        log_calls = joern_instance.runGremlinQuery(log_call_query)[0]

        # deal with each call statement of log_function
        for log_call in log_calls:
            log_call_info = []
            log_call_info.append(log_function)
            # get call file name, location
            log_call_info.append(log_call[0])
            log_call_info.append(log_call[1])
            log_call_info.append(log_call[2])
            # get cdg_list, neighbor_list, ddg_list, static_list

            log_call_infos.append(log_call_info)

    return log_call_infos

"""
@ param ...
@ return ... 
@ caller main
@ callee retrieveLogFunction, getLogInfo
@ involve get logging call infomation from logging name and performing clustering
"""
def cluster_log_context():

    # initialize python-joern instance
    joern_instance = JoernSteps()
    joern_instance.addStepsDir("/data/joern-code/query/")
    joern_instance.setGraphDbURL("http://localhost:7474/db/data/")
    # connect to database
    joern_instance.connectToDatabase()

    # get name of log functions
    log_functions = retrieveLogFunction()
    # get call info of log functions
    log_call_info = getLogInfo(log_functions, joern_instance)

    # cluster by context list()

    # store call info and cluster result



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
        log = analyze_control.nodeAnalysis(log_result)[0]

        # condition node list (control type, id, isCFGNode, type, code)
        cdg_query = '_().getCFGControlByLog(' + log[0] + ',' + order +')'
        cdg_list = joern_instance.runGremlinQuery(cdg_query)[0] # true/false + cond_node


        # add flowlabel to make sure the total context count is at least 5
        # context = control + neighbor
        if len(cdg_list) < contxt_len:
            neighbor_query = '_().getCFGStatementByLog(' + log[0] + ',' + order +')'
            neighbor_list = joern_instance.runGremlinQuery(neighbor_query)[0] #  + cond_node

        # deal with each condition
        for condition in cdg_list:
            context_lists = analyze_control.getCondList(condition, context_lists, joern_instance)

        # deal with each neighbor
        for neighbor in neighbor_list:
            context_lists = analyze_control.getNeighborList(neighbor, context_lists, joern_instance)

        # get ddg node and ddg lists
        ddg_query = '_().getDDG(' + log[0] + ')'
        ddg_nodes = joern_instance.runGremlinQuery(ddg_query)[0]

        # get static string
        static_query = '_().getStaticStr(' + log[0] + ')'
        static_lists = joern_instance.runGremlinQuery(static_query)[0]

        # deal with each ddg_node to get ddg_lists
        for ddg_node in ddg_nodes:
            ddg_lists = analyze_control.getDDGList(ddg_node, ddg_lists, joern_instance)

    return log, cdg_list, neighbor_list, context_lists, ddg_nodes, ddg_lists, static_lists

"""
@ param  user and repos
@ return nothing
@ caller main
@ callee cluster_record
@ involve read from and write back to files
"""
def cluster(user, repos):

    # initialize func_similarity_dict
    analyze_func = file('data/analyze/function' + user + '_' + repos + '.csv', 'rb')
    func_records = csv.reader(analyze_func)
    for func_record in func_records:
        func_similarity_dic[(func_record[0], func_record[1])] = func_record[2]
    analyze_func.close()

    # initialize read file
    analyze_control = file('data/analyz_joern_' + user + '_' + repos + '.csv', 'rb')
    records = csv.reader(analyze_control)
    # initialize write file
    cluster_analyze = file('data/cluster_' + user + '_' + repos + '.csv', 'wb')
    cluster_analyze_writer = csv.writer(cluster_control)
    cluster_analyze_writer.writerow(['commit_message', 'file_name', 'change_type', 'log_node', \
        'cdg_nodes', 'neighbor_nodes', 'context_lists', 'ddg_nodes', 'ddg_lists', 'static_lists', 'store_name', 'log_loc', 'cluster_index'])

    cdg_lists = []
    # traverse the fetch csv file to record cond_lists of each log statement to cdg_lists
    label_lists = []
    for record in islice(records, 1, None):  # remove the table title
        # store cond_lists(index 6)
        cond_lists = json.loads(record[6])
        # remove [[]] cond_list
        cond_lists = myUtil.removeGivenElement([[]], cond_lists)
        cdg_lists.append(cond_lists)
        # label for each entity [log node](index 3)
        label_lists.append(record[3])

    # cluster log statement based on cdg_lists and cdg_nodes(label)
    # cluster_lists = cdg_lists
    cluster_lists = cluster_control.cluster_record(cdg_lists, label_lists)
    # record cluster index of each log statement
    analyze_control.close()
    analyze_control = file('data/analyz_joern_' + user + '_' + repos + '.csv', 'rb')
    records = csv.reader(analyze_control)
    index = 0
    for record in islice(records, 1, None):
        record.append(cluster_lists[index])
        cluster_analyze_writer.writerow(record)
        index += 1

    similarity_control = file('data/similarity_' + user + '_' + repos + '.csv', 'wb')
    similarity_control_writer = csv.writer(similarity_control)
    similarity_control_writer.writerow(["left", "right", "similarity"])
    # dump similarity
    for pair, similarity in similarity_dic.items():
        if pair[0] >= 0 and pair[1] >= 0:
            similarity_control_writer.writerow([pair[0], pair[1], similarity])

    # close files
    cluster_analyze.close()
    analyze_control.close()
    similarity_control.close()



user="squid"
repos="squid"

# main function
similarity_dic = {}
# function similarity dictionary
func_similarity_dic = {}
retrieveLogFunction()