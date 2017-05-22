#-*-coding: utf-8 -*-
import myUtil
import csv
import json
import re
from joern.all import JoernSteps

"""
@ param log function name, fileName name for storing repos info, joern_instance
@ return log info: code, location, file, cdg_list, neighbor_list, ddg_list, static_list, cluster index 
@ caller main
@ callee ...
@ involve get log call info starts from function name
"""
def get_log_info(log_functions, file_name, joern_instance):
    log_call_infos = {}
    # initiation log info writer csv
    out_csv = file(file_name, 'wb')
    out_csv_writer = csv.writer(out_csv)
    out_csv_writer.writerow(['code', 'location', 'file', 'context_list', 'ddg_list', 'static_list'])

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
            ########################################## code, location, file ####################
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
            context_list = myUtil.getContext(str(log_call[0]), joern_instance)
            ddg_list, static_list = myUtil.getDDGAndContent(str(log_call[0]), joern_instance)
            log_call_info.append(json.dumps(context_list))
            log_call_info.append(json.dumps(ddg_list))
            log_call_info.append(json.dumps(static_list))
            out_csv_writer.writerow(log_call_info)

            log_call_infos[log_call[0]] = log_call_info

            record_count += 1
            if record_count%10 == 0:
                print "now analyzing record: %d " %record_count

    out_csv.close()

    return log_call_infos

"""
@ param user and repos
@ return ... 
@ caller main
@ callee retrieveLogFunction, getLogInfo
@ involve get logging call infomation from logging name and performing clustering
"""
def analyze_repos(user, repos):

    # initialize python-joern instance
    joern_instance = JoernSteps()
    joern_instance.addStepsDir("/data/joern-code/query/")
    joern_instance.setGraphDbURL("http://localhost:7474/db/data/")
    # connect to database
    joern_instance.connectToDatabase()
    # get name of log functions
    log_functions = myUtil.retrieveLogFunction('data/fetch/' + repos + '_logging_statement.csv')
    file_name = 'data/fetch/' + user + '_' + repos + '_repos_analyze.csv'
    get_log_info(log_functions, file_name, joern_instance)


"""
main function
"""
if __name__ == "__main__":
    # several configuration constant: user, repos
    # user = 'mongodb'
    # repos = 'mongo'
    # user = 'opencv'
    # repos = 'opencv'
    user = 'Kitware'
    repos = 'CMake'
    # user = 'llvm-mirror'
    # repos = 'clang'
    # user = 'torvalds'
    # repos = 'linux'

    analyze_repos(user, repos)
    