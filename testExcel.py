#-*-coding: utf-8 -*-
# import csv

"""
test for excel
"""
# csvfile = file('test.csv', 'ab')
# writer = csv.writer(csvfile)
# writer.writerow(['id', 'url', 'keywords'])
# data = [
#   ('1', 'http://www.xiaoheiseo.com/', '小黑'),
#   ('2', 'http://www.baidu.com/', '百度'),
#   ('3', 'http://www.jd.com/', '京东')
# ]
# writer.writerows(data)
# csvfile.close()

# with open('test.csv','rb') as csvfile:
#     reader = csv.reader(csvfile)
#     for row in reader:
#        print row

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
a = "asajskas (asjasiadlasdj;"
print a
b = a[a.index('('):]
print b
