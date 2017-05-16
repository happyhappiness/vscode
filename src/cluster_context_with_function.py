#-*-coding: utf-8 -*-
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
@ param log function name, file_name, joern_instance
@ return log info: code, location, file, cdg_list, neighbor_list, ddg_list, static_list, cluster index 
@ caller main
@ callee ...
@ involve get log call info starts from function name
"""
def getLogInfo(log_functions, file_name, joern_instance):
    log_call_infos = {}
    context_lists = []
    # initiation log info writer csv
    out_csv = file(file_name, 'wb')
    out_csv_writer = csv.writer(out_csv)
    out_csv_writer.writerow(['code', 'location', 'file', 'cdg_nodes', \
        'neighbor_node', 'context_list', 'ddg_list', 'static_list', 'cluster_index'])

    # get log statement id from log function name
    record_count = 0
    for log_function in log_functions:
        log_call_query = '_().logToCallStatements("' + log_function +'")'
        log_calls = joern_instance.runGremlinQuery(log_call_query)

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
            fileName = joern_instance.runGremlinQuery(file_query)[0]
            log_call_info.append(fileName[0])
            ########################################## context  #################################
            cdg_list, neighbor_list, context_list, ddg_list, static_list = myUtil.getContextInfo(log_call[0], joern_instance)
            log_call_info.append(json.dumps(cdg_list))
            log_call_info.append(json.dumps(neighbor_list))
            log_call_info.append(json.dumps(context_list))
            log_call_info.append(json.dumps(ddg_list))
            log_call_info.append(json.dumps(static_list))
            log_call_infos[id] = log_call_info
            out_csv_writer.writerow(log_call_info)

            context_list = myUtil.removeGivenElement([[]], context_list)
            context_lists.append(context_list)

            record_count += 1
            if record_count%10 == 0:
                print "now analyzing record: %d " %record_count

    out_csv.close()

    return log_call_infos, context_lists

"""
@ param ...
@ return ... 
@ caller main
@ callee retrieveLogFunction, getLogInfo
@ involve get logging call infomation from logging name and performing clustering
"""
def cluster_log_context(isFromFile):

    # initialize python-joern instance
    joern_instance = JoernSteps()
    joern_instance.addStepsDir("/data/joern-code/query/")
    joern_instance.setGraphDbURL("http://localhost:7474/db/data/")
    # connect to database
    joern_instance.connectToDatabase()

    # get call info of log functions
    call_info_fileName = 'data/analyze/log_info_' + user + '_' + repos + '.csv'
    if isFromFile:
        in_csv = file(call_info_fileName, 'rb')
        records = csv.reader(in_csv)
        log_call_infos = {}
        context_lists = []
        index = 0
        for record in islice(records, 1, None):
            log_call_infos[index] = record
            context_lists.append(json.loads(record[5]))
        in_csv.close()
    else:
        # get name of log functions
        log_functions = retrieveLogFunction()
        log_call_infos, context_lists = getLogInfo(log_functions, call_info_fileName, joern_instance)

    # initialize function similarity dictionary
    similarity_dic_fileName = 'data/analyze/similarity_info_' + user + '_' + repos + '.csv'
    func_similarity_fileName = 'data/analyze/func_similarity_info_' + user + '_' + repos + '.csv'
    func_similarity_dic = myUtil.getFunctionSimilarityDic(False, func_similarity_fileName)

    # perform clustering
    cluster_lists = myUtil.performCluster(context_lists, func_similarity_dic, 0.5, similarity_dic_fileName)
    log_call_infos.values()

    # write back into file
    out_csv = file('data/analyze/cluster_log_info_' + user + '_' + repos + '.csv', 'wb')
    out_csv_writer = csv.writer(out_csv)
    out_csv_writer.writerow(['code', 'location', 'file', 'cdg_node', \
        'neighbor_node', 'context_list', 'ddg_list', 'static_list', 'cluster_index'])
    index = 0
    for key, log_call_info in log_call_infos.items():
        log_call_info.append(cluster_lists[index])
        out_csv_writer.writerow(log_call_info)
        index += 1
    out_csv.close()


"""
main function
"""
if __name__ == "__main__":
    user="squid"
    repos="squid"

    cluster_log_context(True)