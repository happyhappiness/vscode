#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import base64
import json
import myUtil
from itertools import islice
from joern.all import JoernSteps

"""
@ param  user and repos
@ return nothing
@ caller main
@ callee ...
@ involve find same old and new context
"""
def statistics(user, repos):

    # initialize read file
    analysis = file('data/fetch/' + user + '_' + repos + '_old_new_analyze.csv', 'rb')
    records = csv.reader(analysis)
    # initialize write file
    statistic = file('data/fetch/' + user + '_' + repos + '_statistics.csv', 'wb')
    statistic_writer = csv.writer(statistic)
    # traverse to find same old and new context(no context change)
    log_count = 0
    same_count = 0
    for record in records:
        # title
        if log_count == 0:
            statistic_writer.writerow(record)
            log_count += 1
            continue
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
        log_count += 1

    # close files
    analysis.close()
    statistic.close()


"""
main function
"""
if __name__ == "__main__":
    # several configuration constant: user, repos
    # user = 'mongodb'
    # repos = 'mongo'
    # user = 'opencv'
    # repos = 'opencv'
    user = 'Kitware'
    repos = 'CMake'
    # user = 'llvm-mirror'
    # repos = 'clang'
    # user = 'torvalds'
    # repos = 'linux'

    statistics( user, repos)
