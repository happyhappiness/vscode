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
@ param  sha
@ return time info
@ involve access github and fetch time info
"""
def get_time_for_sha(sha, gh):
    commit = gh.repos.commits.get(sha=sha).commit
    time = commit.committer.date
    author = commit.committer.name
    return [time.isoformat(), author]
"""
@ param  user and repos
@ return nothing
@ involve read from and write back to files
"""
def cluster(is_rebuild, z3_api):

    if is_rebuild:
        # initialize read file
        read_file = file(my_constant.ANALYZE_OLD_NEW_JOERN_FILE_NAME, 'rb')
        records = csv.reader(read_file)
        # initialize write file
        write_file = file(my_constant.STATISTICS_OLD_NEW_TEMP_FILE_NAME, 'wb')
        write_file_writer = csv.writer(write_file)
        write_file_writer.writerow(my_constant.STATISTICS_OLD_NEW_TITLE)

        feature_lists = []
        edit_words = []
        gumtree = Gumtree()
        gh = Github(login='993273596@qq.com', password='nx153156', user=my_constant.USER, repo=my_constant.REPOS)
        # traverse the fetch csv file to record cond_lists of each log statement to cdg_lists
        index = 0
        for record in islice(records, 1, None):  # remove the table title
            old_log = record[my_constant.ANALYZE_OLD_NEW_OLD_LOG]
            new_log = record[my_constant.ANALYZE_OLD_NEW_NEW_LOG]
            edit_word, edit_feature = gumtree.get_word_edit_from_log(old_log, new_log)
            old_log_time = get_time_for_sha(record[my_constant.ANALYZE_OLD_NEW_SHA], gh)
            record.append(edit_word)
            record = record + old_log_time + edit_feature
            write_file_writer.writerow(record)
            print 'now processing %d file' %(index)
            index += 1
        read_file.close()
        write_file.close()
        gumtree.close()

    # build feature lists
    read_file = file(my_constant.STATISTICS_OLD_NEW_TEMP_FILE_NAME, 'rb')
    records = csv.reader(read_file)
    feature_lists = []
    for record in islice(records, 1, None):
        if z3_api is not None:
            # old cdg feature
            old_cdg_feature = json.loads(record[my_constant.ANALYZE_OLD_NEW_OLD_CDG_FEATURE])
            old_cdg_z3_feature = z3_api.get_infix_for_postfix(old_cdg_feature)
            feature_lists.append(old_cdg_z3_feature)
        else:
            feature_lists.append(record[-1])
    read_file.close()

    # cluster log statement based on cdg_list and ddg_list
    cluster_lists = cluster_api.cluster_record_with_equality(feature_lists, z3_api)
    # record cluster index of each log statement
    read_file = file(my_constant.STATISTICS_OLD_NEW_TEMP_FILE_NAME, 'rb')
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

    cluster(True, None)
    # z3_api = Z3_api()
    # cluster(z3_api)
