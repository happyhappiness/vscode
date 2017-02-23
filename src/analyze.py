#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import base64

# reload(sys)
# sys.setdefaultencoding('utf-8')
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
@ return edited record array
@ caller analyze
@ callee conca_element
@ involve retrieve context info through ASTVisitor
"""
def deal_line(line, log_index, loc_index, file_index):

    context_info = commands.getoutput('cat download/' + line[file_index] \
                      + '| xargs -0 find-func-decls ' + line[loc_index])
    context_info = context_info.split('@')
    # get source file with store_name
    source_file = open(line[file_index], 'rb')
    source = source_file.readlines()
    source = source.split('\n')
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
        line.pop(file_index)
        line.append(context)
        # upper context(no log)
        log_loc = context.find(line[log_index])
        # break if wrong context
        if log_loc == -1:
            return
        context_up = context[0:log_loc - 1]
        line.append(context_up)
        # downer context(no log)
        log_loc = context.find('\n', log_loc)
        # break if wrong context
        if log_loc == -1:
            return
        context_down = context[log_loc + 1:]
        line.append(context_down)
        return line

"""
@ param  user and repos
@ return nothing
@ caller main
@ callee deal_line
@ involve operate fetch and analyze files
"""
def analyze(user, repos):

    fetch_reader = open('data/fetch_' + user + repos + '.csv', 'rb')
    analyze = file('data/analyz_' + user + repos + '.csv', 'wb')
    analyze_writer = csv.writer(analyze)
    analyze_writer.writerow(['commit_message', 'file_name', 'change_type',\
                        'log_statement', 'context', 'up_context', 'down_context'])
    lines = csv.reader(fetch_reader)
    # traverse the fetch csv file to update context info
    count = 0
    for line in lines:
        if count % 10 == 0:
            print "now analyze the No. %d record" %count
        # do not deal with '-'
        if line[3] == '-':
            continue
        # call deal_line to retrieve location info
        line = deal_line(line, 4, 5, 6)
        # write table title
        line.pop(0)
        analyze_writer.writerow(line)
        count = count + 1
    analyze_writer.close()
    fetch_reader.close()


"""
main function
"""

# several configuration constant: user, repos
user = 'mongodb'
repos = 'mongo'

analyze( user, repos)

