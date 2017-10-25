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
from itertools import islice
from gumtree_api import Gumtree
from srcml_api import SrcmlApi
import gumtree_api
import my_constant
import myUtil

reload(sys);
sys.setdefaultencoding('utf8')

"""
@ param file name and srcml
@ return log record list and call record list
@ involve traverse each function in file to build two sort of repos
"""
def analyze_file(file_name, srcml):
    log_record_list = [] #[file, function, loc, log, check, variable]
    call_record_list = [] #[file, function, calls]
    calls = []
    # handle file to get and store all functions
    """TODO input: file, output:functions"""
    functions = []
    # traverse function to get calls and filter log info
    for function in functions:
        """TODO input: function, output:calls and log locs"""
        calls = []
        log_locs = []
        # build log record for each log location
        for log_loc in log_locs:
            log_record = []
            log_record_list.append(log_record)
    return log_record_list, call_record_list

"""
@ param
@ return 
@ involve traverse repos name and collect all cpp file
"""
def fetch_repos_file(repos_name):
    filenames = []
    # read file from repos dir + repos name if repos name is not None
    if repos_name is not None:
        directory = my_constant.REPOS_DIR + repos_name
    else:
        print "please input a repos name"
    # traverse directory for all cpp like while not test like file
    for item in os.walk(directory):
        for filename in item[2]:
            # filter by cpp like and not test like
            if myUtil.filter_file(filename):
                # concate and store file
                filename = os.path.join(item[0], filename)
                filenames.append(filename)
    return filenames

"""
@ param repos name to analyze and flag about analyze first or last repos
@ return nothing 
@ involve fetch file from given repos and build two sort of repos(log and call)
"""
def analyze_repos(repos_name):
    srcml = SrcmlApi()
    gumtree = Gumtree()
    # fetch file name
    file_names = fetch_repos_file(repos_name)

    # initialize log and call analysis file
    log_file = file(my_constant.ANALYZE_REPOS_LOG_FILE_NAME, 'wb')
    log_writer = csv.writer(log_file)
    log_writer.writerow(my_constant.ANALYZE_REPOS_LOG_TITLE)
    call_file = file(my_constant.ANALYZE_REPOS_CALL_FILE_NAME, 'wb')
    call_writer = csv.writer(call_file)
    call_writer.writerow(my_constant.ANALYZE_REPOS_CALL_TITLE)

    # analyze file in unit of function
    total_file = len(file_names)
    file_cnt = 0
    log_record_cnt = 0
    call_record_cnt = 0
    for file_name in file_names:
        file_cnt += 1
        log_record_list, call_record_list = analyze_file(file_name, srcml)
        for log_record in log_record_list:
            log_writer.writerow(log_record)
        for call_record in call_record_list:
            call_writer.writerow(call_record)
        log_record_cnt += len(log_record_list)
        call_record_cnt += len(call_record_list)
        print 'now analyzing file %d/%d, have found log record %d, call record %d' \
                            %(file_cnt, total_file, log_record_cnt, call_record_cnt)

    # close file
    log_file.close()
    call_file.close()

"""
main function
"""
if __name__ == "__main__":
#    analyze_repos_joern(True)
    analyze_repos("curl-7.1.1")
    gumtree_api.close_jvm()

    