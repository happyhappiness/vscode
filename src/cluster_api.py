#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import json
from itertools import islice
from z3_api import Z3_api
import analyze_control_clone
import myUtil
import my_constant

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
@ param cluster a and b for comparing, similarity_dic, last similarity(1)
@ return similarity value
@ involve compute similarity between clusters (the least similar cond_list pairs)
"""
def compute_similarity_for_cluster(cluster_a, cluster_b, similarity_dic, similarity = 1):

    #  if has record in dictory, then use dictory
    if similarity_dic.get((cluster_a.id, cluster_b.id)) is not None:
        return min(similarity_dic.get((cluster_a.id, cluster_b.id)), similarity)

    # compare cdg_list of entity
    if cluster_a.id >= 0 and cluster_b.id >= 0:
        similarity = min(myUtil.compute_similarity(cluster_a.vec, cluster_b.vec), similarity)
        return similarity

    # first cluster (children)
    if cluster_a.id < 0:
        # traverse children
        for child in cluster_a.children:
            similarity = min(compute_similarity_for_cluster(child, cluster_b, similarity_dic, similarity), similarity)
        return similarity

    # second cluster (children)
    if cluster_b.id < 0:
        # traverse children
        for child in cluster_b.children:
            similarity = min(compute_similarity_for_cluster(cluster_a, child, similarity_dic, similarity), similarity)
        return similarity

"""
@param: cdg_lists(entiry vectors), cluster_similarity = 0.90
@return cluster index for each entity
@involve: cluster entities based on similarity threshold(do not accept)
"""
def cluster_record_with_similarity(feature_lists, cluster_similarity = 0.95):
   
    # initialize the custers to consist of each entity
    myclusters = [mycluster(children=[], vec=feature_lists[i], id=i) for i in range(len(feature_lists))]
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
                        compute_similarity_for_cluster(myclusters[i], myclusters[j], similarity_dic)
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
        mycluster1, mycluster2 = myclusters[flag[0]], myclusters[flag[1]]
        # create new bicluster(cluster id is minus number)
        new_mycluster = mycluster(children=[], id=currentclusted)
        # children is basic level
        if mycluster1.id >= 0:
            new_mycluster.children.append(mycluster1)
        else:
            new_mycluster.children.extend(mycluster1.children)
        if  mycluster2.id >= 0:
            new_mycluster.children.append(mycluster2)
        else:
            new_mycluster.children.extend(mycluster2.children)
        currentclusted -= 1
        # remove old cluster from the clusters
        del myclusters[flag[1]]
        del myclusters[flag[0]]
        myclusters.append(new_mycluster)
        print len(myclusters)

    # compute cluster_lists based on clusters and cluster number
    cluster_lists = [0 for i in range(len(feature_lists))]
    index = 0
    for now_cluster in myclusters:
        if now_cluster.id < 0:
            # traverse children
            for child in now_cluster.children:
                cluster_lists[child.id] = index
        else:
            cluster_lists[now_cluster.id] = index
        index += 1
    return cluster_lists


"""
@ param vector a and b for comparing
@ return true or false
@ involve compute equality between vectors (the least similar cond_list pairs)
"""
def compute_equality(vec_a, vec_b, z3_api):
    if z3_api:
        return z3_api.judge_equality_for_statments(vec_a, vec_b)
    else:
        return vec_a == vec_b

"""
@ param cluster a and b for comparing, similarity_dic
@ return true or false
@ involve compute equality between clusters (the least similar cond_list pairs)
"""
def compute_equality_for_cluster(cluster_a, cluster_b, similarity_dic, z3_api):

    #  if has record in dictory, then use dictory
    if similarity_dic.get((cluster_a.id, cluster_b.id)) is not None:
        return similarity_dic.get((cluster_a.id, cluster_b.id))

    # compare cdg_list of entity
    if cluster_a.id >= 0 and cluster_b.id >= 0:
        return compute_equality(cluster_a.vec, cluster_b.vec, z3_api)


    # first cluster (children)
    if cluster_a.id < 0:
        # first child
        return compute_equality_for_cluster(cluster_a.children[0], cluster_b, similarity_dic, z3_api)

    # second cluster (children)
    if cluster_b.id < 0:
        # first child
        return compute_equality_for_cluster(cluster_a, cluster_b.children[0], similarity_dic, z3_api)

"""
@param: cdg_lists(entiry vectors), cluster_similarity = 0.90
@return cluster index for each entity
@involve: cluster entities based on equality(true/false)
"""
def cluster_record_with_equality(feature_lists, z3_api):

    # initialize the custers to consist of each entity
    myclusters = [mycluster(children=[], vec=feature_lists[i], id=i) for i in range(len(feature_lists))]
    flag = None
    currentclusted = -1
    similarity_dic = {}

    # stop clustering based on culster number ( == 1)
    while len(myclusters) > 1:

        # traverse cluster a and cluster b in clusters
        myclusters_len = len(myclusters)
        for i in range(myclusters_len - 1):
            for j in range(i + 1, myclusters_len):

                # compute similaritys if no record in dictory of similaritys
                if similarity_dic.get((myclusters[i].id, myclusters[j].id)) is None:

                    # compute similaritys by calling computeSim on (vector a, vector b)
                    similarity_dic[(myclusters[i].id, myclusters[j].id)] =\
                        compute_equality_for_cluster(myclusters[i], myclusters[j], similarity_dic, z3_api)
                    # record symmetrical record
                    similarity_dic[(myclusters[j].id, myclusters[i].id)] =\
                                similarity_dic[(myclusters[i].id, myclusters[j].id)]

                #  fetch the similarity
                similarity = similarity_dic[(myclusters[i].id, myclusters[j].id)]
                # find cluster pair with maxest similarity and flag them
                if similarity:
                    flag = (i, j)
                    break
            if similarity:
                break
        if not similarity:
            break
        # combine the two clusters
        mycluster1, mycluster2 = myclusters[flag[0]], myclusters[flag[1]]
        # create new bicluster(cluster id is minus number)
        new_mycluster = mycluster(children=[], id=currentclusted)
        # children is basic level
        if mycluster1.id >= 0:
            new_mycluster.children.append(mycluster1)
        else:
            new_mycluster.children.extend(mycluster1.children)
        if  mycluster2.id >= 0:
            new_mycluster.children.append(mycluster2)
        else:
            new_mycluster.children.extend(mycluster2.children)
        currentclusted -= 1
        # remove unused dict
        for sub_cluster1 in mycluster1.children:
            for sub_cluster2 in mycluster2.children:
                similarity_dic.pop(sub_cluster1.id, sub_cluster2.id)
                similarity_dic.pop(sub_cluster2.id, sub_cluster1.id)
        similarity_dic.pop(mycluster1.id, mycluster2.id)
        similarity_dic.pop(mycluster2.id, mycluster1.id)
        # remove old cluster from the clusters
        del myclusters[flag[1]]
        del myclusters[flag[0]]
        myclusters.append(new_mycluster)
        print len(myclusters)

    # compute cluster_lists based on clusters and cluster number
    cluster_lists = [0 for i in range(len(feature_lists))]
    index = 0
    for now_cluster in myclusters:
        if now_cluster.id < 0:
            # traverse children
            for child in now_cluster.children:
                cluster_lists[child.id] = index
        else:
            cluster_lists[now_cluster.id] = index
        index += 1
    return cluster_lists


"""
main function
"""
if __name__ == "__main__":

    cluster_record_with_similarity([])