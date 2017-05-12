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
@ return log info: code, location, file, cdg_list, neighbor_list, ddg_list, static_list, cluster index 
@ caller main
@ callee ...
@ involve get log call info starts from function name
"""
def getLogInfo(log_functions, joern_instance):
    log_call_infos = {}
    context_lists = []

    # get log statement id from log function name
    for log_function in log_functions:
        log_call_query = '_().logToCallStatements("' + log_function +'")'
        log_calls = joern_instance.runGremlinQuery(log_call_query)

        record_count = 0
        # deal with each call statement of log_function
        for log_call in log_calls:
            # check whether occurred before
            log_call = log_call[0]
            if log_call_infos.has_key(log_call[0]):
                continue
            ########################################## code, location, file #################################
            log_call_info = []
            # code
            log_call_info.append(log_call[1])
            # location
            log_call_info.append(log_call[2])
            # file
            file_query = '_().getFileInfo(' + str(log_call[3]) +')'
            file = joern_instance.runGremlinQuery(file_query)[0]
            log_call_info.append(file[0])
            ########################################## context  #################################
            order = '5'
            context_list = []
            ddg_list = []
            log_call[0] = str(log_call[0])
            # condition node list (control type, id, isCFGNode, type, code)
            cdg_query = '_().getCFGControlByLog(' + log_call[0] + ',' + order +')'
            cdg_list = joern_instance.runGremlinQuery(cdg_query)[0] # true/false + cond_node
            # deal with each condition
            for condition in cdg_list:
                context_list = analyze_control.getCondList(condition, context_list, joern_instance)

            # add flowlabel to make sure the total context count is at least 5
            # context = control + neighbor
            if len(cdg_list) < order:
                neighbor_query = '_().getCFGStatementByLog(' + log_call[0] + ',' + order +')'
                neighbor_list = joern_instance.runGremlinQuery(neighbor_query)[0] #  + cond_node
            # deal with each neighbor
            for neighbor in neighbor_list:
                context_list = analyze_control.getNeighborList(neighbor, context_list, joern_instance)

            # get ddg node and ddg lists
            ddg_query = '_().getDDG(' + log_call[0] + ')'
            ddg_nodes = joern_instance.runGremlinQuery(ddg_query)[0]
            # deal with each ddg_node to get ddg_lists
            for ddg_node in ddg_nodes:
                ddg_list = analyze_control.getDDGList(ddg_node, ddg_list, joern_instance)

            # get static string
            static_query = '_().getStaticStr(' + log_call[0] + ')'
            static_list = joern_instance.runGremlinQuery(static_query)[0]
            log_call_info.append(cdg_list)
            log_call_info.append(neighbor_list)
            log_call_info.append(context_list)
            log_call_info.append(ddg_list)
            log_call_info.append(static_list)
            log_call_infos[id] = log_call_info

            context_list = myUtil.removeGivenElement([[]], context_list)
            context_lists.append(context_list)

            record_count += 1
            if record_count%10 == 0:
                print "now analyzing record: %d " %record_count

    return log_call_infos, context_lists

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
    log_call_infos, context_lists = getLogInfo(log_functions, joern_instance)
    # perform clustering
    cluster_lists = cluster_control.cluster_record(context_lists)
    index = 0
    for log_call_info in log_call_infos:
        log_call_info.append(cluster_lists[index])
        index += 1
    # write back into file
    out_csv = file('data/analyze/logCallInfo_' + user + '_' + repos + '.csv', 'wb')
    out_csv_writer = csv.writer(out_csv)
    out_csv_writer.writerow(['code', 'location', 'file', 'cdg_node', \
        'neighbor_nodes', 'context_lists', 'ddg_lists', 'static_lists', 'cluster_index'])
    out_csv.close()

user="squid"
repos="squid"

# main function
similarity_dic = {}
# function similarity dictionary
func_similarity_dic = {}
cluster_log_context()