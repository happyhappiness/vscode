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
import my_util
import my_constant

reload(sys)
sys.setdefaultencoding('utf-8')

def cluster_feature(z3_api):
    """
    @ param nothing\n
    @ return nothing\n
    @ involve cluster by feature(check and variable)\n
    """
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

    # my_util.dumpSimilarityDic(similarity_dict)
    # close files
    write_file.close()
    read_file.close()

def cluster_edition():
    """
    @ param nothing\n
    @ return nothing\n
    @ involve cluster by edition\n
    """
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

    # my_util.dumpSimilarityDic(similarity_dict)
    # close files
    write_file.close()
    read_file.close()

def cluster_edition_and_feature(z3_api=None):
    """
    @ param z3 api\n
    @ return nothing\n
    @ involve cluster by edition and feature\n
    """
    # initialize read file
    read_file = file(my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME, 'rb')
    records = csv.reader(read_file)

    feature_lists = []
    # build feature list
    index = 0
    for record in islice(records, 1, None):  # remove the table title
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

    # my_util.dumpSimilarityDic(similarity_dict)
    # close files
    write_file.close()
    read_file.close()

def cluster(z3_api=None):
    """
    @ param z3 api\n
    @ return nothing\n
    @ involve cluster by feature and edition/ edition/ feature\n
    """
    cluster_edition_and_feature(z3_api)
    cluster_edition()
    cluster_feature(z3_api)

def generate_class(): 
    """
    @ param nothing\n
    @ return nothing\n
    @ involve generate class for edition and feature cluster\n
    """
    feature_indexes = [my_constant.FETCH_LOG_OLD_LOC, my_constant.FETCH_LOG_OLD_LOG, my_constant.FETCH_LOG_NEW_LOG, \
            my_constant.ANALYZE_FUNCTION, my_constant.ANALYZE_FUNCTION_LOC, my_constant.ANALYZE_CHECK, my_constant.ANALYZE_VARIABLE, my_constant.ANALYZE_EDIT_WORD]
    cluster_api.generate_class_from_cluster(my_constant.CLUSTER_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME,\
        my_constant.CLASS_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME, my_constant.CLASS_OLD_NEW_TITLE, feature_indexes)

"""
main function
"""
if __name__ == "__main__":

    # cluster(None)
    generate_class()
