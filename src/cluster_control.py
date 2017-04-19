#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import json
from itertools import islice

"""
@ param  cond_list of a and b to compute
@ return lenth of common substring / min length
@ callee ...
@ caller computeSim ..
@ involve compute the longgest common string (continuous) of two cond_list
"""
def longestCommonStr(cond_list_a, cond_list_b):

    common_str = []
    len_a = len(cond_list_a) + 1
    len_b = len(cond_list_b) + 1
    len_common = 0
    index_end = 0
    memory = [[0 for col in range(len_b)] for row in range(len_a)]
    for i in range(1, len_a):
        for j in range(1, len_b):
            # update len_common with history
            if cond_list_a[i - 1] == cond_list_b[j-1]:
                memory[i][j] = memory[i-1][j-1] + 1
                len_common = max(memory[i][j], len_common)
            else:
                memory[i][j] = 0

    # simlarity value with common length / min length
    return len_common/min(len_a, len_b)


"""
@ param cond_list a and b for comparing
@ return similarity value
@ callee longestCommonSeq
@ caller computeSim ..
@ involve compute similarity between cond_lists
"""
def computeSim(cond_lists_a, cond_lists_b):
    len_a = len(cond_lists_a)
    len_b = len(cond_lists_b)

    # record the similarity matrix
    memory = [[0 for col in range(len_b)] for row in range(len_a)]
    # similarity between a and b
    sim_value_a_b = 0
    for index_a in range(len_a):
        for index_b in range(len_b):
            best_sim_value_a = 0
            # # various flowLabel --> sim_value = 0
            # sim_value = 0
            # if cond_list_a[1] == cond_list_b[1]:
            # compute similarity between cond_list_a[0] and cond_list_b[0]
            memory[index_a][index_b] = computeSim(cond_lists_a[index_a][0], cond_lists_b[index_b][0])
            best_sim_value_a = max(memory[index_a][index_b], best_sim_value_a)
        # summary total similarity between a and b
        sim_value_a_b += best_sim_value_a
    sim_value_a_b = sim_value_a_b / len_a

    # similarity between b and a
    sim_value_b_a = 0
    for index_b in range(len_b):
        best_sim_value_b = max(memory[:][index_b])
        # summary total similarity between a and b
        sim_value_b_a += best_sim_value_b
    sim_value_b_a = sim_value_b_a / len_b

    return (sim_value_b_a + sim_value_a_b) / 2

"""
@ param  record of fetch_reader line, index of log, index of log_loc, index of store_name
@ return edited record array, has edited flag(log)
@ caller cluster
@ callee computeSim
@ involve clustering log statements based on cdg_lists
"""
def cluster_record( cdg_lists):

    cluster_lists = cdg_lists

    return cluster_lists
"""
@ param  user and repos
@ return nothing
@ caller main
@ callee cluster_record
@ involve read from and write back to files
"""
def cluster(user, repos):

    # initialize read file
    analyze_control = file('data/analyz_joern_' + user + '_' + repos + '.csv', 'rb')
    records = csv.reader(analyze_control)
    # initialize write file
    cluster_control = file('data/cluster_' + user + '_' + repos + '.csv', 'wb')
    cluster_control_writer = csv.writer(cluster_control)
    cluster_control_writer.writerow(['commit_message', 'file_name', 'change_type',\
                         'log_node', 'cdg_nodes', 'condition_lists', 'cluster_index'])

    cdg_lists = []
    # traverse the fetch csv file to record cond_lists of each log statement to cdg_lists
    for record in islice(records, 1, None):  # remove the table title
        # store cond_lists(index 5)
        cond_lists = json.loads(record[5])
        cdg_lists.append(cond_lists)

    # cluster log statement based on cdg_lists
    cluster_lists = cluster_record(cdg_lists)
    # record cluster index of each log statement
    index = 0
    for record in islice(records, 1, None):
        record.append(cluster_lists[index])
        cluster_control_writer.writerow(record)

    # close files
    cluster_control.close()
    analyze_control.close()


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
# user = 'llvm-mirror'
# repos = 'clang'
# user = 'torvalds'
# repos = 'linux'

# cluster( user, repos)
longestCommonStr("SOFTWARE", "LESSONS TEARNED IN SOFTWeeE TE")
