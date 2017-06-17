#-*-coding: utf-8 -*-
# import csv
# from itertools import islice  
"""
test for excel
"""

# """
# split string
# @ param string to split
# @ return splitted list
# @involve split string to list 
# """

# csvfile = file('data/test.csv', 'wb')
# writer = csv.writer(csvfile)
# writer.writerow(['id', 'url', 'keywords'])
# data = []
# list_a = [[1,2],[3,5]]
# data.append(list_a)

# writer.writerows(data)
# csvfile.close()

# csvfile = file('data/test.csv','rb')
# reader = csv.reader(csvfile)
# for row in islice(reader,1,None):
#       print row
# csvfile.close()

"""
test for pickle
not human readable
"""
# import pickle

# list_a = [[1,2],[3,5]]
# with open('data/pickle.txt', 'wb') as fp:
#     pickle.dump(list_a, fp)
# with open ('data/pickle.txt', 'rb') as fp:
#     list_a = pickle.load(fp)

# print list_a


"""
test for json
human readable
"""
# import json
# import csv
# from itertools import islice


# csvfile = file('data/test.csv', 'wb')
# writer = csv.writer(csvfile)
# writer.writerow(['id', 'url', 'keywords'])
# data = []
# list_a = [[['233','12'],[2,4]],[[1,0],[2,3]]]
# list_b = [[1,4],[2,5]]
# data.append(json.dumps(list_a))
# data.append(json.dumps(list_b))
# writer.writerow(data)
# csvfile.close()

# csvfile = file('data/test.csv','rb')
# reader = csv.reader(csvfile)
# for row in islice(reader, 1, None):
#     print row
#     # json do not support single quotation mark
#     list_a = json.loads(row[0])
#     list_b = json.loads(row[1])

# csvfile.close()
"""
test for string replace
"""
# str = 'this is string example....wow!!! this is really string'
# str.replace('is', 'was')
# print str

"""
test for regular expression
"""
# import re

# patch = '+ log2("check your input", num, a);'

# # calculate the parameter num by counting occurence of ','
# param_num = patch.count(',')
# print param_num

# # generate parameter pattern based on parameter number
# param_pattern = '\('
# for i in range(param_num):
#     param_pattern = param_pattern + '(.*),'
# param_pattern = param_pattern + '(.*)\);$'

# # generate the log pattern with combination of param_pattern
# pattern = '^(-|\+)(.*(?:log|debug|print|printf|writeline|write|error).*)' + param_pattern

# # match and output the result
# match_result = re.match(pattern, patch, re.I)
# if match_result:
#     group_num = param_num + 3
#     for i in range(group_num):
#         print match_result.group(i+1).strip()
# else:
#     print "no match"


"""
general test
"""
# a = "asajskas (asjasiadlasdj;"
# print a
# b = a[a.index('('):]
# print b
