# import csv

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

str = 'this is string example....wow!!! this is really string'
str.replace('is', 'was')
print str