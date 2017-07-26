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
                log_file_name = my_constant.SAVE_REPOS_LOG + str(total_log) + '.cpp'
                log_file = open(log_file_name, 'wb')
                log_file.write(log)
                log_file.close()
                writer.writerow([filename, loc, log, log_file_name])
                total_log += 1
        loc += 1

    file_reader.close()
    return total_log
"""
@ param
@ return nothing 
@ involve fetch and analyze each hunk
"""
def fetch_file():

    # read file from directory
    filenames = []
    for item in os.walk(my_constant.REPOS_DIR):
        for filename in item[2]:
            # deal with cpp file
            is_cpp = re.search(my_constant.FILE_FORMAT, filename, re.I)
            if is_cpp:
                filenames.append(os.path.join(item[0], filename))

    repos_file = file(my_constant.ANALYZE_REPOS_FILE_NAME, 'wb')
    repos_writer = csv.writer(repos_file)
    repos_writer.writerow(my_constant.ANALYZE_REPOS_TITLE)
    total_log = 0
    total_file = 0
    # analyze each file to record repos log info
    log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)
    log_function = myUtil.functionToRegrexStr(log_functions)
    gumtree = Gumtree()
    for filename in filenames:
        total_file += 1
        total_log = deal_file(filename, log_function, repos_writer, gumtree, total_log)
        if total_file % 10 == 0:
            print 'have dealed with %d file, have dealed with %d log' %(total_file, total_log)

    # close file
    repos_file.close()
    gumtree.close()

"""
main function
"""
if __name__ == "__main__":
    fetch_file()


    