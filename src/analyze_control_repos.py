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

reload(sys);
sys.setdefaultencoding('utf8')

"""
@ param filename, log function, repos writer, gumtree object and log counter
@ return total_log
@ involve deal with each file and record log info
"""
def deal_file( filename, log_function, writer, gumtree, total_log):

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
                block_file_name = my_constant.SAVE_REPOS_BLOCK + str(total_log) + '.cpp'
                myUtil.save_file(block, block_file_name)
                # get and save function
                function = gumtree.get_function()
                function_file_name = my_constant.SAVE_REPOS_FUNCTION + str(total_log) + '.cpp'
                if function == '':
                    function_loc = loc
                    function = function.join(lines)
                else:
                    function_loc = gumtree.get_function_loc()
                myUtil.save_file(function, function_file_name)                    
                # get block feature
                gumtree.set_file(block_file_name)
                block_feature = gumtree.get_block_feature()
                block_feature = json.dumps(block_feature)
                writer.writerow([filename, loc, log, log_file_name, block, block_file_name, block_feature, function_file_name, function_loc])
                total_log += 1
                gumtree.set_file(filename)
        loc += 1

    file_reader.close()
    return total_log
"""
@ param
@ return nothing 
@ involve fetch and analyze each hunk
"""
def fetch_file(isFromBegin=True, start_file=0, start_log=0):

    # read file from directory
    filenames = []
    for item in os.walk(my_constant.REPOS_DIR):
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


    # support continue from given location
    if isFromBegin:
        repos_gumtree_file = file(my_constant.ANALYZE_REPOS_GUMTREE_FILE_NAME, 'wb')
        repos_gumtree_writer = csv.writer(repos_gumtree_file)
        repos_gumtree_writer.writerow(my_constant.ANALYZE_REPOS_GUMTREE_TITLE)
        total_file = 0
        total_log = 0
    else:
        repos_gumtree_file = file(my_constant.ANALYZE_REPOS_GUMTREE_FILE_NAME, 'ab')
        repos_gumtree_writer = csv.writer(repos_gumtree_file)
        total_file = start_file
        total_log = start_log
    # analyze each file to record repos log info
    log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)
    log_function = myUtil.functionToRegrexStr(log_functions)
    gumtree = Gumtree()
    for filename in filenames[total_file:]:
        total_file += 1
        total_log = deal_file(filename, log_function, repos_gumtree_writer, gumtree, total_log)
        # if total_file % 10 == 0:
        print 'have dealed with %d file, have dealed with %d log' %(total_file, total_log)

    # close file
    repos_gumtree_file.close()
    gumtree.close()

"""
@ param
@ return nothing 
@ involve fetch and analyze each log[ddg and cdg]
"""
def analyze_repos_joern(is_rebuild = False):
    # build joern index and restart database
    if is_rebuild:
        fetch_file()
        myUtil.rebuild_joern_index(my_constant.REPOS_PARENT_DIR + '.joernIndex/', my_constant.REPOS_JOERN_DIR)
    joern = Joern_api()
    repos_gumtree_file = file(my_constant.ANALYZE_REPOS_GUMTREE_FILE_NAME, 'rb')
    repos_gumtree_records = csv.reader(repos_gumtree_file)
    repos_joern_file = file(my_constant.ANALYZE_REPOS_JOERN_FILE_NAME, 'wb')
    repos_joern_writer = csv.writer(repos_joern_file)
    repos_joern_writer.writerow(my_constant.ANALYZE_REPOS_JOERN_TITLE)

    total_record = 0
    total_log = 0
    # get ddg and cdg with joern
    for record in islice(repos_gumtree_records, 1, None):
        if joern.set_log(record[my_constant.ANALYZE_REPOS_FUNCTION_FILE], int(record[my_constant.ANALYZE_REPOS_FUNCTION_LOC])):
            ddg = json.dumps(joern.get_argument_type())
            cdg = json.dumps(joern.get_control_dependence())
            repos_joern_writer.writerow(record + [ddg, cdg])
            total_log += 1
        print 'have dealed with %d record %d log' %(total_record, total_log)
        total_record += 1

    repos_gumtree_file.close()
    repos_joern_file.close()


"""
main function
"""
if __name__ == "__main__":
   analyze_repos_joern()



    