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
import commands
import base64
import json
from itertools import islice
from gumtree_api import Gumtree
import my_constant
import myUtil

reload(sys)
sys.setdefaultencoding('utf-8')

"""
@ param hunk record, log writer, gumtree object and log counter
@ return total_log
@ involve deal with each hunk and retieve log info
"""
def deal_hunk( hunk_record, writer, gumtree, total_log):
    old_log_loc = json.loads(hunk_record[my_constant.FETCH_HUNK_OLD_LOG_LOC])
    new_log_loc = json.loads(hunk_record[my_constant.FETCH_HUNK_NEW_LOG_LOC])
    old_hunk_loc = int(hunk_record[my_constant.FETCH_HUNK_OLD_HUNK_LOC])
    new_hunk_loc = int(hunk_record[my_constant.FETCH_HUNK_NEW_HUNK_LOC])
    old_hunk_file = hunk_record[my_constant.FETCH_HUNK_OLD_HUNK_FILE]
    new_hunk_file = hunk_record[my_constant.FETCH_HUNK_NEW_HUNK_FILE]

    hunk_info = hunk_record[:-4]
    gumtree.set_old_new_file(old_hunk_file, new_hunk_file)
    gumtree.add_old_log_nodes(old_log_loc)
    gumtree.add_new_log_nodes(new_log_loc)
    action_type = gumtree.get_hunk_edited_type()

    # deal with log existing in old file
    for old_loc in old_log_loc:
        if gumtree.set_old_loc(old_loc):
            # log loc in old hunk, old loc and old log
            old_hunk_log_loc = old_loc # index from 0
            old_loc = old_hunk_loc + old_loc - 1 # index from 0
            old_log = gumtree.get_old_log()

            # log loc in new hunk, new loc and new log
            new_loc = gumtree.get_new_loc()
            new_log = gumtree.get_new_log()
            # if map
            if new_loc != -1:
                # remove mapping new_log_loc
                if new_loc in new_log_loc:
                    new_log_loc.remove(new_loc)
                new_loc = new_hunk_loc + new_loc - 1
            new_hunk_log_loc = new_loc + 1 - new_hunk_loc
            # whether this old log is edited
            curr_action_type = action_type + gumtree.is_old_log_edited()
            writer.writerow(hunk_info + [old_hunk_log_loc, new_hunk_log_loc, old_loc, new_loc, old_log, new_log, curr_action_type])
            total_log += 1

    # deal with inserted log
    for new_loc in new_log_loc:
        if gumtree.set_new_loc(new_loc):
            # new loc and new log
            new_hunk_log_loc = new_loc
            new_loc = new_hunk_loc + new_loc - 1
            new_log = gumtree.get_new_log()

            # old loc and old log
            old_loc = -1
            old_hunk_log_loc = old_loc + 1 - old_hunk_loc
            old_log = None

            # curr action type
            curr_action_type = action_type + 1
            writer.writerow(hunk_info + [old_hunk_log_loc, new_hunk_log_loc, old_loc, new_loc, old_log, new_log, curr_action_type])
            total_log += 1

    return total_log

"""
@ param
@ return nothing 
@ involve fetch and analyze each hunk
"""
def fetch_hunk():

    # initiate csvfile
    hunk_file = file(my_constant.FETCH_HUNK_FILE_NAME, 'rb')
    hunk_records = csv.reader(hunk_file)

    log_file = file(my_constant.FETCH_LOG_FILE_NAME, 'wb')
    log_writer = csv.writer(log_file)
    log_writer.writerow(my_constant.FETCH_LOG_TITLE)

    total_log = 0
    total_hunk = 0
    gumtree = Gumtree()
    for hunk_record in islice(hunk_records, 1, None):
        total_hunk += 1
        total_log = deal_hunk(hunk_record, log_writer, gumtree, total_log)
        if total_hunk % 10 == 0:
            print 'have dealed with %d hunk, have dealed with %d log' %(total_hunk, total_log)

    # close file
    hunk_file.close()
    log_file.close()
    gumtree.close()

"""
main function
"""
if __name__ == "__main__":
    fetch_hunk()
    