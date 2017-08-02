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
import commands
import base64
import json
from pygithub3 import Github
from itertools import islice
from gumtree_api import Gumtree
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
                # save block
                block_file_name = my_constant.SAVE_REPOS_BLOCK + str(total_log) + '.cpp'
                block_file = open(block_file_name, 'wb')
                block_file.write(block)
                block_file.close()
                # get block feature
                block_feature = gumtree.get_block_feature()
                block_feature = json.dumps(block_feature)
                writer.writerow([filename, loc, log, log_file_name, block, block_file_name, block_feature])
                total_log += 1
        loc += 1

    file_reader.close()
    return total_log
"""
@ param
@ return nothing 
@ involve fetch and analyze each hunk
"""
def fetch_file(isFromBegin, start_file, start_log):

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
        repos_file = file(my_constant.ANALYZE_REPOS_FILE_NAME, 'wb')
        repos_writer = csv.writer(repos_file)
        repos_writer.writerow(my_constant.ANALYZE_REPOS_TITLE)
        total_file = 0
        total_log = 0
    else:
        repos_file = file(my_constant.ANALYZE_REPOS_FILE_NAME, 'ab')
        repos_writer = csv.writer(repos_file)
        total_file = start_file
        total_log = start_log
    # analyze each file to record repos log info
    log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)
    log_function = myUtil.functionToRegrexStr(log_functions)
    gumtree = Gumtree()
    for filename in filenames[total_file:]:
        total_file += 1
        total_log = deal_file(filename, log_function, repos_writer, gumtree, total_log)
        # if total_file % 10 == 0:
        print 'have dealed with %d file, have dealed with %d log' %(total_file, total_log)

    # close file
    repos_file.close()
    gumtree.close()

"""
main function
"""
if __name__ == "__main__":
    fetch_file(True,742, 2040)

    # filenames = []
    # for item in os.walk('User'):
    #     for filename in item[2]:
    #         # deal with cpp file
    #         is_cpp = re.search(my_constant.FILE_FORMAT, filename, re.I)
    #         if is_cpp:
    #             is_unsupport = re.search(my_constant.UNSPORT_FILE_FORMAT, filename, re.I)
    #             if is_unsupport:
    #                 filename = os.path.join(item[0], filename)
    #                 new_filename = filename.replace(is_unsupport.group(), '.cpp')
    #                 os.rename(filename, new_filename)
    #                 print new_filename
    #                 filenames.append(new_filename)



    