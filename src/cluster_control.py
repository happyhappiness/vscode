#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import json
import myUtil
from itertools import islice

"""
@ param  cond_list of a and b to compute, func_similarity_dic
@ return lenth of common substring / min length
@ callee ...
@ caller computeSim ..
@ involve compute the longgest common string (continuous) of two cond_list
"""
def longestCommonStr(cond_list_a, cond_list_b, func_similarity_dic):

    # if just one element, then compare that
    len_a = len(cond_list_a)
    len_b = len(cond_list_b)
    if len_a == 0 or len_b == 0:
        if (len_a + len_b) == 0:
            return float(1)
        else:
            return float(0)
    # length of a and b
    len_a += 1
    len_b += 1

    # find first common and build the common matrix(a*b)
    memory = [[0 for col in range(len_b)] for row in range(len_a)]
    index_a = 0
    index_b = 0
    first_len_common = 0
    for i in range(1, len_a):
        for j in range(1, len_b):
            # update len_common with history
            if cond_list_a[i - 1] == cond_list_b[j-1]:
                memory[i][j] = memory[i-1][j-1] + 1
                if first_len_common < memory[i][j]:
                    first_len_common = memory[i][j]
                    index_a = i
                    index_b = j
                continue
            # use func_similarity_dic firstly (similarity between callee is greater than 0.5)
            if func_similarity_dic.has_key((cond_list_a[i - 1], cond_list_b[j - 1])):
                memory[i][j] = memory[i-1][j-1] + 1
                if first_len_common < memory[i][j]:
                    first_len_common = memory[i][j]
                    index_a = i
                    index_b = j
            else:
                memory[i][j] = 0

    len_common = first_len_common
    # filter the totally different and equal condition
    if len_common in range(1, min(len_a, len_b)):
        curr_a = 0
        curr_b = 0
        # find all common in road decide by index_a, index_b
        # forward [1, index_a - 1]
        for i in range(1, min(index_a, index_b)):
            # last common <-- element behind is 0
            curr_a = index_a - i
            curr_b = index_b - i
            if memory[curr_a][curr_b] > 0 and memory[curr_a + 1][curr_b + 1] == 0:
                len_common += memory[curr_a][curr_b]

        # backward [index_a + 1, len_a - 1]
        for i in range(1, min(len_a - index_a, len_b - index_b)):
            # last common <-- element behind is 0
            curr_a = index_a + i
            curr_b = index_b + i
            if memory[curr_a][curr_b] > 0 and (curr_a == len_a - 1 or curr_b == len_b - 1 or memory[curr_a + 1][curr_b + 1] == 0):
                len_common += memory[curr_a][curr_b]

    # simlarity value with common length / min length (0, 1)
    # return float(len_common)/min(len_a, len_b)
    return float(len_common)*2/(len_a + len_b - 2)


"""
@ param cond_list a and b for comparing, func_similarity_dic
@ return similarity value
@ callee longestCommonSeq
@ caller computeSimForCluster ..
@ involve compute similarity between cond_lists, unordered common element
"""
def computeSim(cond_lists_a, cond_lists_b, func_similarity_dic):
    len_a = len(cond_lists_a)
    len_b = len(cond_lists_b)

    # do not deal with 0 exception at this period
    if len_a == 0 or len_b == 0:
        return float(0)

    # record the similarity dictionary
    memory = {}
    # build similarity dictionary between a and b
    sim_value_a_b = 0
    for index_a in range(len_a):
        for index_b in range(len_b):
            # add one element is elements share higher similarity than 0.5
            curr_similarity = longestCommonStr(cond_lists_a[index_a][0], \
                            cond_lists_b[index_b][0], func_similarity_dic)
            if curr_similarity > 0.5:
                memory[(index_a, index_b)] = curr_similarity

    # iterate to find maxest and remove corresponding line and row
    # initialization
    len_common = 0
    values_list = memory.values()
    len_values = len(values_list)
    while len_values != 0:
        # find max element and remove corresponding row and col
        max_value = max(values_list)
        myUtil.removeDicElement(memory, values_list.index(max_value))
        # iterator
        len_common += 1
        values_list = memory.values()
        len_values = len(values_list)

    return (len_common)*2 / (len_a + len_b) # (0, 1)

"""
@param vec, left, right, similarity, id
@return new cluster
@involve cluster class with children and similarity between children
"""
class mycluster:
    def __init__(self, vec=None, children=None, similarity=0.0, id=None):
        # for drawing picture of clusters
        self.children = children
        # feature vector
        self.vec = vec
        #  id label for locating label
        self.id = id
        self.similarity = similarity


"""
@ param cluster a and b for comparing, similarity_dic, func_similarity_dic, last similarity(1)
@ return similarity value
@ callee computeSim(cond_list_a, cond_list_b); self
@ caller cluster_record ..
@ involve compute similarity between clusters (the least similar cond_list pairs)
"""
def computeSimForCluster(cluster_a, cluster_b, similarity_dic, func_similarity_dic, similarity = 1):

    #  if has record in dictory, then use dictory
    if similarity_dic.get((cluster_a.id, cluster_b.id)) is not None:
        return min(similarity_dic.get((cluster_a.id, cluster_b.id)), similarity)

    # compare cdg_list of entity
    if cluster_a.id >= 0 and cluster_b.id >= 0:
        similarity = min(computeSim(cluster_a.vec, cluster_b.vec, func_similarity_dic), similarity)
        return similarity

    # first cluster (children)
    if cluster_a.id < 0:
        # traverse children
        for child in cluster_a.children:
            similarity = min(computeSimForCluster(child, cluster_b, similarity_dic, func_similarity_dic, similarity), similarity)
        return similarity

    # second cluster (children)
    if cluster_b.id < 0:
        # traverse children
        for child in cluster_b.children:
            similarity = min(computeSimForCluster(cluster_a, child, similarity_dic, func_similarity_dic, similarity), similarity)
        return similarity

"""
@param: cdg_lists(entiry vectors), func_similarity_dic, cluster_similarity = 0.5
@return cluster index for each entity
@caller cluster
@callee computeSimForCluster
@involve: cluster entities based on similarity
"""
def cluster_record(cdg_lists, func_similarity_dic, cluster_similarity = 0.5):
    # initialize the custers to consist of each entity
    myclusters = [mycluster(children=[], vec=cdg_lists[i], id=i) for i in range(len(cdg_lists))]
    flag = None
    currentclusted = -1
    similarity_dic = {}

    # stop clustering based on culster number ( == 1)
    while len(myclusters) > 1:
        # the miniest similarity to merge two cluster
        max_sim = cluster_similarity

        # traverse cluster a and cluster b in clusters
        myclusters_len = len(myclusters)
        for i in range(myclusters_len - 1):
            for j in range(i + 1, myclusters_len):

                # compute similaritys if no record in dictory of similaritys
                if similarity_dic.get((myclusters[i].id, myclusters[j].id)) is None:

                    # compute similaritys by calling computeSim on (vector a, vector b)
                    similarity_dic[(myclusters[i].id, myclusters[j].id)] =\
                                 computeSimForCluster(myclusters[i], myclusters[j], similarity_dic, func_similarity_dic)
                    # record symmetrical record
                    similarity_dic[(myclusters[j].id, myclusters[i].id)] =\
                                similarity_dic[(myclusters[i].id, myclusters[j].id)]

                #  fetch the similarity
                similarity = similarity_dic[(myclusters[i].id, myclusters[j].id)]
                # find cluster pair with maxest similarity and flag them
                if similarity > max_sim:
                    max_sim = similarity
                    flag = (i, j)
        # stop clusterring when similarity is too small
        if max_sim == cluster_similarity:
            break
        # combine the two clusters
        mycluster1, mycluster2 = flag
        # create new bicluster(cluster id is minus number)
        new_mycluster = mycluster(children=[], similarity=max_sim, id=currentclusted)
        # children is basic level
        if myclusters[mycluster1].id >= 0:
            new_mycluster.children.append(myclusters[mycluster1])
        else:
            new_mycluster.children.extend(myclusters[mycluster1].children)

        if  myclusters[mycluster2].id >= 0:
            new_mycluster.children.append(myclusters[mycluster2])
        else:
            new_mycluster.children.extend(myclusters[mycluster2].children)
        currentclusted -= 1
        # remove old cluster from the clusters
        # have not destroy it
        del myclusters[mycluster2]
        del myclusters[mycluster1]
        myclusters.append(new_mycluster)

    # compute cluster_lists based on clusters and cluster number
    cluster_lists = [0 for i in range(len(cdg_lists))]
    index = 0
    for now_cluster in myclusters:
        if now_cluster.id < 0:
            # traverse children
            for child in now_cluster.children:
                cluster_lists[child.id] = index
        else:
            cluster_lists[now_cluster.id] = index
        index += 1
    return cluster_lists, similarity_dic

"""
@ param  user and repos
@ return nothing
@ caller main
@ callee cluster_record
@ involve read from and write back to files
"""
def cluster(user, repos):

    # initialize func_similarity_dict
    func_similarity_dic = myUtil.getFunctionSimilarityDic(False, 'data/analyz_function_' + user + '_' + repos + '.csv')

    # initialize read file
    analyze_control = file('data/analyz_joern_' + user + '_' + repos + '.csv', 'rb')
    records = csv.reader(analyze_control)
    # initialize write file
    cluster_control = file('data/cluster_' + user + '_' + repos + '.csv', 'wb')
    cluster_control_writer = csv.writer(cluster_control)
    cluster_control_writer.writerow(['commit_message', 'file_name', 'change_type', 'log_node', \
        'cdg_node', 'neighbor_node', 'context_list', 'ddg_node', 'ddg_list', 'static_list', 'store_name', 'log_loc', 'cluster_index'])

    context_lists = []
    # traverse the fetch csv file to record cond_lists of each log statement to cdg_lists
    label_lists = []
    for record in islice(records, 1, None):  # remove the table title
        # store cond_lists(index 6)
        context_list = json.loads(record[6])
        # remove [[]] cond_list
        context_list = myUtil.removeGivenElement([[]], context_list)
        context_lists.append(context_list)
        # label for each entity [log node](index 3)
        label_lists.append(record[3])

    # cluster log statement based on cdg_lists and cdg_nodes(label)
    # cluster_lists = cdg_lists
    cluster_lists, similarity_dic = cluster_record(context_lists, func_similarity_dic, 0.5)
    # record cluster index of each log statement
    analyze_control.close()
    analyze_control = file('data/analyz_joern_' + user + '_' + repos + '.csv', 'rb')
    records = csv.reader(analyze_control)
    index = 0
    for record in islice(records, 1, None):
        record.append(cluster_lists[index])
        cluster_control_writer.writerow(record)
        index += 1

    myUtil.dumpSimilarityDic(similarity_dic, 'data/similarity_' + user + '_' + repos + '.csv')

    # close files
    cluster_control.close()
    analyze_control.close()

"""
main function
"""
if __name__ == "__main__":
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

    # longestCommonStr(["the", "happy","thanks", "dealing", "try","final"], ["the", "sad", "thanks", "dealing", "im", "final"])
    cluster( user, repos)