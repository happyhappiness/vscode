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
@ param
@ return nothing
@ involve cluster by cdg and ddg feature
"""
def cluster_feature(z3_api):
    # initialize read file
    read_file = file(my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME, 'rb')
    records = csv.reader(read_file)

    feature_lists = []
    # build feature list
    index = 0
    for record in islice(records, 1, None):  # remove the table title
        check_feature = json.loads(record[my_constant.ANALYZE_CHECK])
        variable_feature = json.loads(record[my_constant.ANALYZE_VARIABLE])
        # z3 feature
        if z3_api is not None:
            check_feature = z3_api.get_infix_for_postfix(check_feature)
            print 'now processing %d file' %(index)
            index += 1
        feature_lists.append([check_feature, variable_feature])
    read_file.close()

    # cluster log statement based on cdg_list and ddg_list
    cluster_lists = cluster_api.cluster_record_with_equality(feature_lists, z3_api)
    # record cluster index of each log statement
    read_file = file(my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME, 'rb')
    write_file = file(my_constant.CLUSTER_FEATURE_OLD_NEW_FILE_NAME, 'wb')
    write_file_writer = csv.writer(write_file)
    write_file_writer.writerow(my_constant.CLUSTER_OLD_NEW_TITLE)
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
@ param
@ return nothing
@ involve cluster by modification
"""
def cluster_edition():
    # initialize read file
    read_file = file(my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME, 'rb')
    records = csv.reader(read_file)

    feature_lists = []
    # build feature list
    index = 0
    for record in islice(records, 1, None):  # remove the table title
        # old cdg feature
        edit_feature = json.loads(record[my_constant.ANALYZE_EDIT_FEATURE])
        feature_lists.append(edit_feature)
        # print 'now analyzing index: %d' %(index)
        # index += 1
    read_file.close()

    # cluster log statement based on cdg_list and ddg_list
    cluster_lists = cluster_api.cluster_record_with_equality(feature_lists)
    # record cluster index of each log statement
    read_file = file(my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME, 'rb')
    write_file = file(my_constant.CLUSTER_EDITION_OLD_NEW_FILE_NAME, 'wb')
    write_file_writer = csv.writer(write_file)
    write_file_writer.writerow(my_constant.CLUSTER_OLD_NEW_TITLE)
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
@ param
@ return nothing
@ involve cluster by modification and feature
"""
def cluster_edition_and_feature(z3_api=None):
    # initialize read file
    read_file = file(my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME, 'rb')
    records = csv.reader(read_file)

    feature_lists = []
    # build feature list
    index = 0
    for record in islice(records, 122, None):  # remove the table title
        # context feature
        check_feature = json.loads(record[my_constant.ANALYZE_CHECK])
        variable_feature = json.loads(record[my_constant.ANALYZE_VARIABLE])
        # z3 feature
        if z3_api is not None:
            check_feature = z3_api.get_infix_for_postfix(check_feature)
            print 'now processing %d file' %(index)
        index += 1
        # edit feature
        edit_feature = json.loads(record[my_constant.ANALYZE_EDIT_FEATURE])
        print index
        feature_lists.append([check_feature, variable_feature, edit_feature])
    read_file.close()

    # cluster log statement based on cdg_list and ddg_list
    cluster_lists = cluster_api.cluster_record_with_equality(feature_lists, z3_api)
    # record cluster index of each log statement
    read_file = file(my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME, 'rb')
    write_file = file(my_constant.CLUSTER_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME, 'wb')
    write_file_writer = csv.writer(write_file)
    write_file_writer.writerow(my_constant.CLUSTER_OLD_NEW_TITLE)
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
@ param  user and repos
@ return nothing
@ involve cluster by feature and edition
"""
def cluster(z3_api=None):
    cluster_edition_and_feature(z3_api)
    cluster_feature(z3_api)
    cluster_edition()

"""
main function
"""
if __name__ == "__main__":

    cluster(None)
