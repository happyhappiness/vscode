#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import json
import analyze_control_clone
from itertools import islice
from pygithub3 import Github
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
def cluster(z3_api):

    # initialize read file
    analyze_control = file(my_constant.ANALYZE_OLD_NEW_JOERN_FILE_NAME, 'rb')
    records = csv.reader(analyze_control)
    # initialize write file
    cluster_control = file(my_constant.STATISTICS_OLD_NEW_FILE_NAME, 'wb')
    cluster_control_writer = csv.writer(cluster_control)
    cluster_control_writer.writerow(my_constant.STATISTICS_OLD_NEW_TITLE)

    feature_lists = []
    old_log_times = []
    gumtree = Gumtree()
    gh = Github(login='993273596@qq.com', password='nx153156', user=my_constant.USER, repo=my_constant.REPOS)
    # traverse the fetch csv file to record cond_lists of each log statement to cdg_lists
    index = 0
    for record in islice(records, 1, None):  # remove the table title
        # get old and new log feature
        old_log_file = record[my_constant.ANALYZE_OLD_NEW_OLD_LOG_FILE]
        new_log_file = record[my_constant.ANALYZE_OLD_NEW_NEW_LOG_FILE]
        edit_words, edit_feature = gumtree.get_word_edit(old_log_file, new_log_file)
        old_log_times.append(get_time_for_sha(record[my_constant.ANALYZE_OLD_NEW_SHA], gh))
        if z3_api is not None:
            # old cdg feature
            old_cdg_feature = json.loads(record[my_constant.ANALYZE_OLD_NEW_OLD_CDG_FEATURE])
            old_cdg_z3_feature = z3_api.get_infix_for_postfix(old_cdg_feature)
            feature_lists.append(old_cdg_z3_feature)
        else:
            feature_lists.append(edit_feature)
        print 'now processing %d file' %(index)
        index += 1

    # cluster log statement based on cdg_list and ddg_list
    cluster_lists = cluster_api.cluster_record_with_equality(feature_lists, z3_api)
    # record cluster index of each log statement
    analyze_control.close()
    analyze_control = file(my_constant.ANALYZE_OLD_NEW_JOERN_FILE_NAME, 'rb')
    records = csv.reader(analyze_control)
    index = 0
    for record in islice(records, 1, None):
        record = record + [json.dumps(edit_words[index])] + old_log_times[index] + [cluster_lists[index]]
        cluster_control_writer.writerow(record)
        index += 1

    # myUtil.dumpSimilarityDic(similarity_dict)
    # close files
    cluster_control.close()
    analyze_control.close()
    gumtree.close()

"""
main function
"""
if __name__ == "__main__":

    cluster(None)
    # z3_api = Z3_api()
    # cluster(z3_api)
