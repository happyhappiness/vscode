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
from itertools import islice
from gumtree_api import Gumtree
import my_constant
import myUtil

"""
@ param log record, log function, old new writer, gumtree object and log counter
@ return total_log
@ involve deal with each old new log and save log info
"""
def deal_log( log_record, writer, total_log):

    old_log = log_record[my_constant.FETCH_LOG_OLD_LOG]
    new_log = log_record[my_constant.FETCH_LOG_NEW_LOG]
    # do not deal with LOG_NO_MODIFY
    action_type = log_record[my_constant.FETCH_LOG_ACTION_TYPE]
    # no modification of this log statement
    if int(action_type) % 2 == 0:
        return total_log
    # write old and new log file
    old_log_file_name = my_constant.SAVE_OLD_LOG + str(total_log) + '.cpp'
    log_file = open(old_log_file_name, 'wb')
    log_file.write(old_log)
    log_file.close()
    new_log_file_name = my_constant.SAVE_NEW_LOG + str(total_log) + '.cpp'
    log_file = open(new_log_file_name, 'wb')
    log_file.write(new_log)
    log_file.close()
    writer.writerow(log_record + [old_log_file_name, new_log_file_name])
    total_log += 1

    return total_log
"""
@ param
@ return nothing 
@ involve fetch and analyze each hunk
"""
def fetch_old_new_gumtree():

    # read record from fetched log
    log_file = file(my_constant.FETCH_LOG_FILE_NAME, 'rb')
    log_records = csv.reader(log_file)        
    old_new_gumtree_file = file(my_constant.ANALYZE_OLD_NEW_GUMTREE_FILE_NAME, 'wb')
    old_new_gumtree_writer = csv.writer(old_new_gumtree_file)
    old_new_gumtree_writer.writerow(my_constant.ANALYZE_OLD_NEW_GUMTREE_TITLE)

    total_log = 0
    total_record = 0
    for log_record in islice(log_records, 1, None):
        total_record += 1
        total_log = deal_log(log_record, old_new_gumtree_writer, total_log)
        if total_record % 10 == 0:
            print 'have dealed with %d record, have dealed with %d log' %(total_record, total_log)

    # close file
    log_file.close()
    old_new_gumtree_file.close()

"""
@ param
@ return nothing 
@ involve fetch and analyze each log[ddg and cdg]
"""
def analyze_old_new(is_rebuild = False):
    # build joern index and restart database
    if is_rebuild:
        fetch_old_new_gumtree()
    old_new_gumtree_file = file(my_constant.ANALYZE_OLD_NEW_GUMTREE_FILE_NAME, 'rb')
    old_new_gumtree_records = csv.reader(old_new_gumtree_file)
    old_new_llvm_file = file(my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME, 'wb')
    old_new_llvm_writer = csv.writer(old_new_llvm_file)
    old_new_llvm_writer.writerow(my_constant.ANALYZE_OLD_NEW_LLVM_TITLE)

    total_record = 0
    total_log = 0
    gumtree = Gumtree()
    # get ddg and cdg with joern
    for record in islice(old_new_gumtree_records, 1, None):
        old_check = []
        new_check = []
        old_variable = []
        new_variable = []
        # depended statement locations
        ddg_codes = set()
        ddg_locs = set()
        # is_ddg_modified = gumtree.get_function_edited_type(ddg_locs)
        # if is_ddg_modified:
        #     record[my_constant.FETCH_LOG_ACTION_TYPE] = my_constant.LOG_LOG_FEATURE_MODIFY
        # else:
        #     record[my_constant.FETCH_LOG_ACTION_TYPE] = my_constant.LOG_LOG_MODIFY
        old_new_llvm_writer.writerow(record + [json.dumps(old_check), json.dumps(old_variable), \
                    json.dumps(new_check), json.dumps(new_variable), ddg_codes, ddg_locs])
        print 'have dealed with %d record; %d log' %(total_record, total_log)
        total_log += 1
        total_record += 1

    old_new_gumtree_file.close()
    old_new_llvm_file.close()
    gumtree.close()


"""
main function
"""
if __name__ == "__main__":
    analyze_old_new(True)

    # analyze_old_new_joern(False)
    # gumtree = Gumtree()
    # get_function("second/download/CMake/CMake-old-new/CMake-old-new/Kitware_CMake_old_file_517.cpp",\
    #             1879, gumtree)
    # gumtree.close()
