#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import base64
from itertools import islice  


"""
@ param  string array arr and begin index(include) and end index(not include) 
@ return string by concanating element from begin to end index 
@ caller  deal_line
@ callee ..
@ involve concanate string element of array
"""
def conca_element(arr, begin, end):
    conca_str = ''
    for i in range(begin, end):
        conca_str = conca_str + arr[i] + '\n'
    return conca_str


"""
@ param  record of fetch_reader line, index of log, index of log_loc, index of store_name
@ return edited record array and has edited flag
@ caller analyze
@ callee conca_element
@ involve retrieve context info through ASTVisitor
"""
def deal_line(line, log_index, loc_index, file_index):

    has_edit = False
    context_info = commands.getoutput('cat ' + line[file_index] \
                      + '| xargs -0 find-func-decls ' + line[loc_index])
    context_info = context_info.split('@')
    # get source file with store_name
    source_file = open(line[file_index], 'rb')
    source = source_file.readlines()
    source_file.close()
    # formal output should be array with len = 4
    context_info_len = len(context_info)
    if context_info_len >= 4:
        # loc info
        start_loc = int(context_info[context_info_len - 3])
        end_loc = int(context_info[context_info_len - 2])
        # whole contex
        context = conca_element(source, start_loc - 1, end_loc)
        # remove log_loc, store_name and add context, context_up, context_down
        line.pop(loc_index)
        line.pop(file_index - 1)
        line.append(context)
        has_edit = True
        # upper context(no log)
        log_loc = context.find(line[log_index])
        # record the right context
        if log_loc != -1:
            context_up = context[0:log_loc - 1]
            line.append(context_up)
            # downer context(no log)
            log_loc = context.find('\n', log_loc)
            # record the right context
            if log_loc != -1:
                context_down = context[log_loc + 1:]
                line.append(context_down)

    return line, has_edit

"""
@ param  user and repos
@ return nothing
@ caller main
@ callee deal_line
@ involve operate fetch and analyze files
"""
def analyze(user, repos):

    fetch = file('data/fetch_' + user + '_' + repos + '.csv', 'rb')
    analyze = file('data/analyz_' + user + '_' + repos + '.csv', 'wb')
    analyze_writer = csv.writer(analyze)
    analyze_writer.writerow(['commit_message', 'file_name', 'change_type',\
                        'log_statement', 'context', 'up_context', 'down_context'])
    lines = csv.reader(fetch)
    # traverse the fetch csv file to update context info
    count = 0
    # remove the table title
    for line in islice(lines, 1, None):
        if count % 10 == 0:
            print "now record the No. %d analyze" %count
        # do not deal with '-'
        # if line[3] == '-':
        #     continue
        # call deal_line to retrieve location info
        line, has_edit = deal_line(line, 4, 5, 6)
        # update analyze data is has edited
        if has_edit:
            line.pop(0)
            analyze_writer.writerow(line)
            count = count + 1
    # close files
    analyze.close()
    fetch.close()


"""
main function
"""

# several configuration constant: user, repos
user = 'mongodb'
repos = 'mongo'

analyze( user, repos)

