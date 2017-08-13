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
from joern_api import Joern_api
import my_constant
import myUtil

reload(sys);
sys.setdefaultencoding('utf8')

"""
@ param log record, log function, old new writer, gumtree object and log counter
@ return total_log
@ involve deal with each old new log and save info
"""
def deal_log( log_record, writer, gumtree, total_log):

    old_log = log_record[my_constant.FETCH_LOG_OLD_LOG]
    new_log = log_record[my_constant.FETCH_LOG_NEW_LOG]
    old_file_name = log_record[my_constant.FETCH_LOG_OLD_FILE]
    old_loc = log_record[my_constant.FETCH_LOG_OLD_LOC]
    # do not deal with LOG_NO_MODIFY
    action_type = log_record[my_constant.FETCH_LOG_ACTION_TYPE]
    # no modification of this log statement
    if int(action_type) % 2 == 0:
        return total_log
    # write old and new log file
    old_log_file_name = my_constant.SAVE_OLD_NEW_OLD_LOG + str(total_log) + '.cpp'
    log_file = open(old_log_file_name, 'wb')
    log_file.write(old_log)
    log_file.close()
    new_log_file_name = my_constant.SAVE_OLD_NEW_NEW_LOG + str(total_log) + '.cpp'
    log_file = open(new_log_file_name, 'wb')
    log_file.write(new_log)
    log_file.close()
    # write block file
    gumtree.set_file(old_file_name)
    block = ""
    block_file_name = my_constant.SAVE_OLD_NEW_BLOCK + str(total_log) + '.cpp'
    function_file_name = my_constant.SAVE_OLD_NEW_FUNCTION + str(total_log) + '.cpp'
    block_feature = []
    if gumtree.set_loc(int(old_loc)):
        block = gumtree.get_block()
        myUtil.save_file(block, block_file_name)
        # get block feature
        gumtree.set_file(block_file_name)
        block_feature = gumtree.get_block_feature()
        block_feature = json.dumps(block_feature)
        # get function feature
        function = gumtree.get_function()
        myUtil.save_file(function, function_file_name)
    writer.writerow(log_record + [old_log_file_name, new_log_file_name, block, block_file_name, block_feature, function_file_name])
    total_log += 1

    return total_log
"""
@ param
@ return nothing 
@ involve fetch and analyze each hunk
"""
def fetch_old_new():

    # read record from fetched log
    log_file = file(my_constant.FETCH_LOG_FILE_NAME, 'rb')
    log_records = csv.reader(log_file)        
    old_new_gumtree_file = file(my_constant.ANALYZE_OLD_NEW_GUMTREE_FILE_NAME, 'wb')
    old_new_gumtree_writer = csv.writer(old_new_gumtree_file)
    old_new_gumtree_writer.writerow(my_constant.ANALYZE_OLD_NEW_GUMTREE_TITLE)

    total_log = 0
    total_record = 0
    gumtree = Gumtree()
    for log_record in islice(log_records, 1, None):
        total_record += 1
        total_log = deal_log(log_record, old_new_gumtree_writer, gumtree, total_log)
        # if total_record % 10 == 0:
        print 'have dealed with %d record, have dealed with %d log' %(total_record, total_log)

    # close file
    log_file.close()
    old_new_gumtree_file.close()
    gumtree.close()

"""
@ param
@ return nothing 
@ involve fetch and analyze each log[ddg and cdg]
"""
def analyze_old_new_joern():
    # build joern index and restart database
    myUtil.rebuild_joern_index(my_constant.OLD_NEW_PARENT_DIR, my_constant.OLD_NEW_JOERN_DIR)
    joern = Joern_api()
    old_new_gumtree_file = file(my_constant.ANALYZE_OLD_NEW_GUMTREE_FILE_NAME, 'rb')
    old_new_gumtree_records = csv.reader(old_new_gumtree_file)
    old_new_joern_file = file(my_constant.ANALYZE_OLD_NEW_JOERN_FILE_NAME, 'wb')
    old_new_joern_writer = csv.writer(old_new_joern_file)
    old_new_joern_writer.writerow(my_constant.ANALYZE_OLD_NEW_JOERN_TITLE)

    for record in old_new_gumtree_records:
        joern.set_log(record[my_constant.ANALYZE_OLD_NEW_OLD_FILE_NAME], int(record[my_constant.ANALYZE_OLD_NEW_OLD_LOC]))
        ddg = json.dumps(joern.get_argument_type())
        cdg = json.dumps(joern.get_control_dependence())
        old_new_joern_writer.writerow(record + [ddg, cdg])

    old_new_gumtree_file.close()
    old_new_joern_file.close()


"""
main function
"""
if __name__ == "__main__":
    fetch_old_new()
    analyze_old_new_joern()
