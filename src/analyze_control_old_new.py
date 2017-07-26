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
@ param log record, log function, old new writer, gumtree object and log counter
@ return total_log
@ involve deal with each old new log and save info
"""
def deal_log( log_record, writer, total_log):

    log = log_record[my_constant.FETCH_LOG_OLD_LOG]
    log_file_name = my_constant.SAVE_OLD_NEW_LOG + str(total_log) + '.cpp'
    log_file = open(log_file_name, 'wb')
    log_file.write(log)
    log_file.close()
    writer.writerow(log_record + [log_file_name])
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
    old_new_file = file(my_constant.ANALYZE_OLD_NEW_FILE_NAME, 'wb')
    old_new_writer = csv.writer(old_new_file)
    old_new_writer.writerow(my_constant.ANALYZE_OLD_NEW_TITLE)
    total_log = 0
    total_record = 0
    for log_record in islice(log_records, 1, None):
        total_record += 1
        total_log = deal_log(log_record, old_new_writer, total_log)
        if total_record % 10 == 0:
            print 'have dealed with %d record, have dealed with %d log' %(total_record, total_log)

    # close file
    log_file.close()
    old_new_file.close()

"""
main function
"""
if __name__ == "__main__":
    fetch_old_new()