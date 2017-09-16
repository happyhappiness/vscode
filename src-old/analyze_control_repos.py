#-*-coding: utf-8 -*-
"""
input: hunk info
BY: gumtree
output: log info
log info [hunk info, log type, old log statement, new log statement, log action]
"""
import csv
import sys
import re
import os
import json
import commands
import base64
from pygithub3 import Github
from itertools import islice
from gumtree_api import Gumtree
from joern_api import Joern_api
import my_constant
import myUtil
import analyze_control_repos_cluster

reload(sys);
sys.setdefaultencoding('utf8')

"""
@ param filename, log function, gumtree object and log counter
@ return total_log
@ involve deal with each file and record log info
"""
def deal_file( filename, log_function, gumtree, joern, total_log):
    logs = []
    gumtree.set_file(filename)
    file_reader = open(filename, 'rb')
    lines = file_reader.readlines()
    loc = 0
    for line in lines:
        is_log = re.search(log_function, line, re.I)
        if is_log:
            if gumtree.set_loc(loc):
                # get and save log
                log = gumtree.get_log()
                # save log
                log_file_name = my_constant.SAVE_REPOS_LOG + str(total_log) + '.cpp'
                log_file = open(log_file_name, 'wb')
                log_file.write(log)
                log_file.close()
                # get and save block
                block = gumtree.get_block()
                block_file_name = my_constant.SAVE_REPOS_LOG_BLOCK + str(total_log) + '.cpp'
                myUtil.save_file(block, block_file_name)              
                # get block feature
                gumtree.set_file(block_file_name)
                block_feature = json.dumps(gumtree.get_block_feature())
                # get condition info
                condition_info = json.dumps(())
                ddg_feature = json.dumps([])
                if joern.set_log(filename, loc):
                    ddg_feature = json.dumps(joern.get_argument_type())
                    condition_info = json.dumps(joern.get_control_dependence())
                # # get and save function
                # function = gumtree.get_function()
                # function_file_name = my_constant.SAVE_REPOS_FUNCTION + str(total_log) + '.cpp'
                # if function == '':
                #     function_loc = loc
                #     function = function.join(lines)
                # else:
                #     function_loc = gumtree.get_function_loc()
                # myUtil.save_file(function, function_file_name)

                logs.append([filename, loc, block, block_file_name, block_feature,\
                    log, log_file_name, ddg_feature, condition_info])
                total_log += 1
                gumtree.set_file(filename)
        loc += 1

    file_reader.close()
    return logs, total_log

"""
@ param joern
@ return nothing 
@ involve retrieve and normalize each condition for basic block[condition]
"""
def fetch_basic_block(gumtree, joern):
    # write to joern analysis file
    repos_basic_block_file = file(my_constant.ANALYZE_REPOS_BASIC_BLOCK_FILE_NAME, 'wb')
    repos_basic_block_writer = csv.writer(repos_basic_block_file)
    repos_basic_block_writer.writerow(my_constant.ANALYZE_REPOS_BASIC_BLOCK_TITLE)

    total_record = 0
    records = joern.get_all_condition()
    for record in records:
        file_name = record[my_constant.ANALYZE_REPOS_BASIC_BLOCK_FILE]
        loc = record[my_constant.ANALYZE_REPOS_BASIC_BLOCK_LOC]
        condition_info = json.dumps(record[2])
        normalized_condition = json.dumps(record[3])
        gumtree.set_file(file_name)
        if gumtree.set_loc(int(loc) - 1):
            # get and save block
            block = gumtree.get_block()
            block_file_name = my_constant.SAVE_REPOS_BASIC_BLOCK_BLOCK + str(total_record) + '.cpp'
            myUtil.save_file(block, block_file_name)
            # get block feature
            gumtree.set_file(block_file_name)
            block_feature = json.dumps(gumtree.get_block_feature())
            record = [file_name, loc, block, block_file_name, block_feature, condition_info, normalized_condition]
            repos_basic_block_writer.writerow(record)
            total_record += 1
            print 'block feature have dealed with %d record' %(total_record)

    repos_basic_block_file.close()

"""
@ param
@ return normalized file names 
@ involve change .c/h to .cpp file
"""
def read_file_name_from_directory(directory):
    # read file from directory
    filenames = []
    for item in os.walk(directory):
        for filename in item[2]:
            # deal with cpp file
            is_cpp = re.search(my_constant.FILE_FORMAT, filename, re.I)
            if is_cpp:
                is_unsupport = re.search(my_constant.UNSRCML_FILE_FORMAT, filename, re.I)
                filename = os.path.join(item[0], filename)
                # transform format to be supported
                if is_unsupport:
                    new_filename = filename.replace(is_unsupport.group(), '.cpp')
                    os.rename(filename, new_filename)
                    filenames.append(new_filename)
                else:
                    filenames.append(filename)
    return filenames

"""
@ param
@ return nothing 
@ involve fetch and analyze each hunk
"""
def fetch_log(gumtree, joern, isFromBegin=True, start_file=0, start_log=0):

    # read file from directory
    filenames = read_file_name_from_directory(my_constant.REPOS_DIR)

    # support continue from given location
    if isFromBegin:
        repos_log_file = file(my_constant.ANALYZE_REPOS_LOG_FILE_NAME, 'wb')
        repos_log_writer = csv.writer(repos_log_file)
        repos_log_writer.writerow(my_constant.ANALYZE_REPOS_LOG_TITLE)
    else:
        repos_log_file = file(my_constant.ANALYZE_REPOS_LOG_FILE_NAME, 'ab')
        repos_log_writer = csv.writer(repos_log_file)
    total_file = start_file
    total_log = start_log

    # analyze each file to record repos log info
    log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)
    log_function = myUtil.functionToRegrexStr(log_functions)
    # build class index from clustered basic block(condition info, condition...)
    class_file = file(my_constant.ANALYZE_REPOS_BASIC_BLOCK_FILE_NAME, 'rb')
    records = csv.reader(class_file)
    class_index = {}
    for record in islice(records, 1, None):
        condition_info = myUtil.get_tuple_from_list(json.loads(record[my_constant.ANALYZE_REPOS_BASIC_BLOCK_CONDITION_IFNO]))
        class_index[condition_info] = record[my_constant.ANALYZE_REPOS_BASIC_BLOCK_NORMALIZED_CONDITION:]

    # deal with each file and get log condition info based on class index
    for filename in filenames[total_file:]:
        logs, total_log = deal_file(filename, log_function, gumtree, joern, total_log)
        for log_record in logs:
            condition_info = log_record[my_constant.ANALYZE_REPOS_CONDITION_INFO]
            if class_index.has_key(condition_info):
                log_record += class_index[condition_info]
                repos_log_writer.writerow(log_record)
            else:
                print "no condition tupe" + condition_info
        # if total_file % 10 == 0:
        print 'have dealed with %d file, have dealed with %d log' %(total_file, total_log)
        total_file += 1

    # close file
    repos_log_file.close()

"""
@ param
@ return nothing 
@ involve fetch and analyze each log[ddg and cdg]
"""
def analyze_repos_joern(is_rebuild = False):
 
    joern = Joern_api()
    gumtree = Gumtree()
    # restart database
    if is_rebuild:
        # fetch all basic block
        fetch_basic_block(gumtree, joern)
    # cluster to get class info
    analyze_control_repos_cluster.cluster()
    # log info + [normalized condition, z3 feature, class index]
    fetch_log(gumtree, joern)
    gumtree.close()


"""
main function
"""
if __name__ == "__main__":
#    analyze_repos_joern(True)
    analyze_repos_joern()

    