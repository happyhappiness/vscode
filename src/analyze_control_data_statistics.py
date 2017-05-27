#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import base64
import json
import myUtil
from itertools import islice
# from joern.all import JoernSteps

"""
@ param  user and repos
@ return nothing
@ caller main
@ callee ...
@ involve find same old and new context
"""
def statistics():

    # initialize read file
    analysis = file(myUtil.ANALYZE_OLD_NEW_FILE_NAME, 'rb')
    records = csv.reader(analysis)
    # initialize write file
    statistic = file(myUtil.STATISTICS_OLD_NEW_FILE_NAME, 'wb')
    statistic_writer = csv.writer(statistic)
    statistic_writer.writerow(myUtil.ANALYZE_OLD_NEW_TITLE)
    # traverse to find same old and new context(no context change)
    log_count = 0
    same_count = 0
    for record in islice(records, 1, None):
        log_count += 1
        # traverse data
        print "commit sha is %s, old loc is %s, new loc is %s."\
                 %(record[0], record[5], record[7])
        # old_context_list 8 new_context_list 9
        old_context_list = json.loads(record[9])
        new_context_list = json.loads(record[10])
        if old_context_list == new_context_list:
            statistic_writer.writerow(record)
            same_count += 1
        print "now analyze the No. %d log, %d is same context" %(log_count, same_count)

    # close files
    analysis.close()
    statistic.close()


"""
main function
"""
if __name__ == "__main__":

    statistics()
