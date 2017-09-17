#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import json
from itertools import islice
from gumtree_api import Gumtree
from z3_api import Z3_api
import cluster_api
import myUtil
import my_constant

"""
@ param  user and repos
@ return nothing
@ involve read from and write back to files
"""
def cluster(z3_api):

    # initialize read file
    read_file = file(my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME, 'rb')
    records = csv.reader(read_file)

    feature_lists = []
    gumtree = Gumtree()
    # build feature list
    index = 0
    for record in islice(records, 1, None):  # remove the table title
        # z3 feature
        if z3_api is not None:
            # old cdg feature
            old_check_feature = json.loads(record[my_constant.ANALYZE_OLD_CHECK])
            old_check_z3_feature = z3_api.get_infix_for_postfix(old_check_feature)
            feature_lists.append(old_check_z3_feature)
        # edit feature
        else:
            feature_lists.append(record[my_constant.ANALYZE_EDIT_FEATURE])
        # print 'now processing %d file' %(index)
        index += 1
    read_file.close()
    gumtree.close()

    # cluster log statement based on cdg_list and ddg_list
    cluster_lists = cluster_api.cluster_record_with_equality(feature_lists, z3_api)
    # record cluster index of each log statement
    read_file = file(my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME, 'rb')
    write_file = file(my_constant.STATISTICS_OLD_NEW_FILE_NAME, 'wb')
    write_file_writer = csv.writer(write_file)
    write_file_writer.writerow(my_constant.STATISTICS_OLD_NEW_TITLE)
    records = csv.reader(read_file)
    index = 0
    for record in islice(records, 1, None):
        record = record + [cluster_lists[index]]
        write_file_writer.writerow(record)
        index += 1

    # myUtil.dumpSimilarityDic(similarity_dict)
    # close files
    write_file.close()
    read_file.close()

"""
main function
"""
if __name__ == "__main__":

    cluster(None)
    # z3_api = Z3_api()
    # cluster(z3_api)
