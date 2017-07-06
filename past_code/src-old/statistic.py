#-*-coding: utf-8 -*-
import csv
import sys
import re
from itertools import islice


"""
@ param  log  partial log statement, statistics_writer
@ return bool flag about whether have constant text or not
@ caller main
@ callee
@ involve analyze partial log statment with regrex and count those with constant text
"""
def statistic(log, statistics_writer):

    data_row = []
    data_row.append(log)

    # analyze partial log statement with regrex
    has_constant_text = False
    constant_text = re.match(".*(\".*\").*", log, re.I)
    if constant_text:
        data_row.append(constant_text.group(1).strip())
        has_constant_text = True
    statistics_writer.writerow(data_row)

    return has_constant_text


"""
main function
"""

# several configuration constant: user, repos
# user = 'mongodb'
# repos = 'mongo'
# user = 'opencv'
# repos = 'opencv'
user = 'apple'
repos = 'swift'

# analyze reader
analyze = file('data/analyz_' + user + '_' + repos + '.csv', 'rb')
lines = csv.reader(analyze)

# statistics writer and table 
statistics = file('data/statistics_' + user + '_' + repos + '.csv', 'wb')
statistics_writer = csv.writer(statistics)
statistics_writer.writerow(['log statement', 'constant text'])

# traverse the analyze csv file to do statistics
count = 0
text_count = 0

# remove the table title
for line in islice(lines, 1, None):

    if count % 10 == 0:
        print "now record the No. %d analyze" %count

    # call statistics to analyze partial log statment
    # index for log statment is 3
    has_constant_text = statistic(line[3], statistics_writer)

    # update text_count number
    if has_constant_text:
        text_count = text_count + 1

    # update count for log dealed
    count = count + 1

print "log statement with constant text is %d " %text_count
# close files
analyze.close()
statistics.close()

