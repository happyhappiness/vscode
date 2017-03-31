#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import base64
from itertools import islice
from joern.all import JoernSteps

"""
@ param  result list
@ return list of analyzed node info
@ callee ...
@ caller getDependendedAstOfLog ..
@ analyze query node. include : id, isCFGNode, type, code
"""
def cdgNodeAnalysis(result):

    cfg_list = []
    for record in result:
        value_list = []
        value_list.append(record._id)
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

    # query for log statement
    location = location + ':'
    base_query = 'getStatementByFileAndLoc("' + filename + '","' + location + '")'
    log_result = joern_instance.runGremlinQuery(base_query)
    # if no log node found return null
    if not log_result:
        return [],[],[]

    # query for ddg and cdg
    order = '5'
    cdg_edge = '["CONTROLS"]'
    ddg_edge = '["REACHES"]'
    cdg_query = base_query + '.sliceBackFromArgument(' + order + ',' + cdg_edge +').astNodes()'
    ddg_query = base_query + '.sliceBackFromArgument(' + order + ',' + ddg_edge +').astNodes()'

    cdg_result = joern_instance.runGremlinQuery(cdg_query)
    ddg_result = joern_instance.runGremlinQuery(ddg_query)

    # analysis query result (id, isCFGNode, type, code)
    log = cdgNodeAnalysis(log_result)
    cdg_list = cdgNodeAnalysis(cdg_result)
    ddg_list = cdgNodeAnalysis(ddg_result)

    return log, cdg_list, ddg_list

"""
@ param  record of fetch_reader line, index of log, index of log_loc, index of store_name
@ return edited record array and has edited flag
@ caller analyze
@ callee getDependendedAstOfLog
@ involve retrieve context info through joern database
"""
def analyze_record( joern_instance, record, log_index, loc_index, file_index):

    loc = record[loc_index]
    filename = '*' + record[file_index]

    # query database with loc and filename
    log, cdg_list, ddg_list = getDependendedAstOfLog(filename, loc, joern_instance)

    record[log_index] = log
    record[loc_index] = cdg_list
    record[file_index] = ddg_list

    return record

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
                         'log_node', 'cdg_nodes', 'ddg_nodes'])
    # initialize read file
    records = csv.reader(fetch)
    # initialize python-joern instance
    joern_instance = JoernSteps()
    joern_instance.addStepsDir("/opt/joern-code/query/")
    joern_instance.setGraphDbURL("http://localhost:7474/db/data/")
    # connect to database
    joern_instance.connectToDatabase()

    # traverse the fetch csv file to update context info
    count = 0
    # remove the table title
    for record in islice(records, 1, None):
        # do not deal with delete log at this version
        if record[3] == '-':
            print "delete record -> ignore"
        if count % 10 == 0:
            print "now record the No. %d analyze" %count
        # call deal_line to retrieve location info(- included)
        record, has_edit = analyze_record(joern_instance, record, 4, 5, 6)

        # update analyze data is has edited
        if has_edit:
            record.pop(0)
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
user = 'opencv'
repos = 'opencv'
# user = 'apple'
# repos = 'swift'

analyze( user, repos)
