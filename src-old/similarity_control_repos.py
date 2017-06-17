#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import json
import myUtil
import my_constant
import analyze_control_clone
from itertools import islice


"""
@ param cond_list a and b for comparing, func_similarity_dic
@ return similarity value
@ callee longestCommonSeq
@ caller compute_cluster ..
@ involve compute similarity between cond_lists, unordered common element
"""
def compute_similarity_for_context(context_list_a, context_list_b, func_similarity_dic):
    cdg_list_a = context_list_a[0]
    ddg_list_a = context_list_a[1]

    cdg_list_b = context_list_b[0]
    ddg_list_b = context_list_b[1]
    if analyze_control_clone.compute_ddg_similarity \
            (ddg_list_a, ddg_list_b, func_similarity_dic) == 1:
        return analyze_control_clone.compute_context_similarity\
                    (cdg_list_a, cdg_list_b, func_similarity_dic)
    return float(0)

"""
@param: cdg_lists(entiry vectors), func_similarity_dic, cluster_similarity = 0.5
@return cluster index for each entity
@caller cluster
@callee computeSimForCluster
@involve: create cluster for log snnippets with high similarity
"""
def compute_cluster(context_lists, func_similarity_dic):


    # dictionary for cluster info
    len_repos = len(context_lists)
    repos_cluster_vec = [0 for i in range(len_repos)]
    func_similarity_dic = myUtil.getFunctionSimilarityDic(True)

    cluster_cnt = 1
    for i in range(len_repos):
        for j in range(len_repos):
            if i == j:
                continue
            if compute_similarity_for_context\
                    (context_lists[i], context_lists[j], func_similarity_dic) == 1:
                # have been saved in one cluster, so with transition, merge the later with the first
                if not repos_cluster_vec[i] == 0:
                    cluster_i = repos_cluster_vec[i]
                    if not repos_cluster_vec[j] == 0:
                        cluster_j = repos_cluster_vec[j]
                        # update repos_cluster_dic to i cluster
                        for k in range(len_repos):
                            if repos_cluster_vec[k] == cluster_j:
                                repos_cluster_vec[k] = cluster_i
                    else:
                        # the later no class, avoid traverse
                        repos_cluster_vec[j] = cluster_i
                    continue
                # have been saved in the later one, so with transition, add the first into the later
                if not repos_cluster_vec[j] == 0:
                    repos_cluster_vec[i] = repos_cluster_vec[j]
                    continue
                # both no cluster, so create new one
                repos_cluster_vec[i] = cluster_cnt
                repos_cluster_vec[j] = cluster_cnt
                cluster_cnt += 1

    return repos_cluster_vec
"""
@ param ...
@ return nothing
@ caller main
@ callee compute_cluster
@ involve compute similarity of repos records
"""
def similarity_control_repos():

    # initialize func_similarity_dict
    func_similarity_dic = myUtil.getFunctionSimilarityDic(True)

    # initialize read file
    analyze_control = file(my_constant.ANALYZE_REPOS_FILE_NAME, 'rb')
    records = csv.reader(analyze_control)

    # initialize write file
    cluster_control = file(my_constant.CLUSTER_REPOS_FILE_NAME, 'wb')
    cluster_control_writer = csv.writer(cluster_control)
    cluster_control_writer.writerow(my_constant.CLUSTER_REPOS_TITLE)

    context_lists = []
    # traverse the fetch csv file to record cond_lists of each log statement to cdg_lists
    for record in islice(records, 1, None):  # remove the table title
        # store cond_lists(index 6)
        cdg_list = json.loads(record[my_constant.ANALYZE_REPOS_CONTEXT])
        ddg_list = json.loads(record[my_constant.ANALYZE_REPOS_DDG])
        # # remove [[]] cond_list
        # context_list = myUtil.removeGivenElement([[]], context_list)
        context_lists.append([cdg_list, ddg_list])

    # cluster log statement based on cdg_list and ddg_list
    repos_cluster_vec = compute_cluster(context_lists, func_similarity_dic)

    # record cluster index of each log statement
    analyze_control.close()
    analyze_control = file(my_constant.ANALYZE_REPOS_FILE_NAME, 'rb')
    records = csv.reader(analyze_control)
    index = 0
    for record in islice(records, 1, None):
        record.append(repos_cluster_vec[index])
        cluster_control_writer.writerow(record)
        index += 1

    # close files
    analyze_control.close()
    cluster_control.close()

"""
main function
"""
if __name__ == "__main__":

    similarity_control_repos()
