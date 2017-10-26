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
from srcml_api import SrcmlApi
from gumtree_api import Gumtree
from llvm_api import LLVM
import gumtree_api
import my_constant
import my_util

reload(sys)
sys.setdefaultencoding('utf-8')

def deal_log( log_record, gumtree, writer, total_log):
    """
    @ param log record, gumtree object and writer and log counter\n
    @ return log counter\n
    @ involve deal with each log and save log info[function and edition]\n
    """
    # filter log that has no modification LOG_NO_MODIFY
    action_type = log_record[my_constant.FETCH_LOG_ACTION_TYPE]
    if int(action_type) % 2 == 0:
        return total_log
    # old loc and old file
    old_loc = log_record[my_constant.FETCH_LOG_OLD_LOC]
    old_file = log_record[my_constant.FETCH_LOG_OLD_FILE]
    new_loc = log_record[my_constant.FETCH_LOG_NEW_LOC]
    new_file = log_record[my_constant.FETCH_LOG_NEW_FILE]
    temp_file = my_constant.GUMTREE_DIR + 'temp.cpp'
    # get function and function loc
    function = new_log = old_log = ''
    function_loc = -1
    # parse old log if is not insert
    if old_loc != '-1':
        # use srcml parser(.cpp temp file)
        my_util.copy_file(old_file, temp_file)
        gumtree.set_file(temp_file)
        if gumtree.set_loc(int(old_loc)):
            old_log = gumtree.get_log()
            function = gumtree.get_function()
            function_loc = gumtree.get_function_loc()
    # parse new log if is not delete
    if new_loc != '-1':
        my_util.copy_file(new_file, temp_file)
        gumtree.set_file(temp_file)
        if gumtree.set_loc(int(new_loc)):
            new_log = gumtree.get_log()
            # refresh function if is insert(update so care about old context)
            if old_loc == '-1':
                function = gumtree.get_function()
                function_loc = gumtree.get_function_loc()
    # write old and new log file as well as function file
    function_file_name = my_constant.SAVE_FUNCTION + str(total_log) + '.cpp'
    my_util.save_file(function, function_file_name)
    old_log_file_name = my_constant.SAVE_OLD_LOG + str(total_log) + '.cpp'
    my_util.save_file(old_log, old_log_file_name)
    new_log_file_name = my_constant.SAVE_NEW_LOG + str(total_log) + '.cpp'
    my_util.save_file(new_log, new_log_file_name)
    # get edit word and feature
    edit_words, edit_feature = gumtree.get_word_edit_from_log(old_log, new_log)
    # get edit type
    gumtree.set_old_new_file(old_log_file_name, new_log_file_name)
    if new_loc == '-1':
        edit_types = ['removeLog']
    elif old_loc == '-1':
        edit_types = ['addLog']
    else:
        edit_types = gumtree.get_log_edited_type()
    log_record[my_constant.FETCH_LOG_OLD_LOG] = old_log
    log_record[my_constant.FETCH_LOG_NEW_LOG] = new_log
    writer.writerow(log_record + [old_log_file_name, new_log_file_name, function_file_name, function_loc, json.dumps(edit_types), edit_words, json.dumps(edit_feature)])
    total_log += 1

    return total_log

def fetch_old_new_gumtree(gumtree):
    """
    @ param gumtree object\n
    @ return nothing \n
    @ involve fetch and analyze each log record\n
    """
    # read record from fetched log
    log_file = file(my_constant.FETCH_LOG_FILE_NAME, 'rb')
    log_records = csv.reader(log_file)
    old_new_gumtree_file = file(my_constant.ANALYZE_OLD_NEW_GUMTREE_FILE_NAME, 'wb')
    old_new_gumtree_writer = csv.writer(old_new_gumtree_file)
    old_new_gumtree_writer.writerow(my_constant.ANALYZE_OLD_NEW_GUMTREE_TITLE)
    # call deal log to deal with each record
    total_log = 0
    total_record = 0
    for log_record in islice(log_records, 1, None):
        total_record += 1
        total_log = deal_log(log_record, gumtree, old_new_gumtree_writer, total_log)
        if total_record % 10 == 0:
            print 'have dealed with %d record, have dealed with %d log' %(total_record, total_log)

    # close file
    log_file.close()
    old_new_gumtree_file.close()

def analyze_old_new(is_rebuild = False):
    """
    @ param flag about whether rebuild(function and edition info)\n
    @ return nothing \n
    @ involve fetch and analyze each log[ddg and cdg]\n
    """
    # if to rebuild, then call fetch_old_new_gumtree to analyze log record
    gumtree = Gumtree()
    if is_rebuild:
        fetch_old_new_gumtree(gumtree)
    # intiate csv file
    old_new_gumtree_file = file(my_constant.ANALYZE_OLD_NEW_GUMTREE_FILE_NAME, 'rb')
    old_new_gumtree_records = csv.reader(old_new_gumtree_file)
    old_new_llvm_file = file(my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME, 'wb')
    old_new_llvm_writer = csv.writer(old_new_llvm_file)
    old_new_llvm_writer.writerow(my_constant.ANALYZE_OLD_NEW_LLVM_TITLE)

    total_record = 0
    total_log = 0
    for record in islice(old_new_gumtree_records, 1, None):
        if total_record % 10 == 0:
            print 'have dealed with %d record; %d log' %(total_record, total_log)
        total_record += 1
        # call srcml to get check and variable info
        function = record[my_constant.ANALYZE_FUNCTION]
        function_loc = record[my_constant.ANALYZE_FUNCTION_LOC]
        srcml = SrcmlApi()
        srcml.set_function_file(function)
        check = []
        variable = []
        if srcml.set_log_loc(int(function_loc)):
            if srcml.set_control_dependence():
                check = srcml.get_control_info()
            variable = srcml.get_log_info()
        # do not keep empty check(not diagnosis log)
        if check == []:
            continue
        # depended statement locations
        ddg_codes = set()
        ddg_locs = set()
        old_new_llvm_writer.writerow(record + [json.dumps(check), json.dumps(variable), ddg_codes, ddg_locs])
        total_log += 1

    # close file
    old_new_gumtree_file.close()
    old_new_llvm_file.close()


"""
main function
"""
if __name__ == "__main__":
    analyze_old_new(True)
    gumtree_api.close_jvm()
