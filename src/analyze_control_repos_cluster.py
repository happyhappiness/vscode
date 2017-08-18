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
import block
import myUtil
import my_constant

    
"""
@param vec, left, right, similarity, id
@return new cluster
@involve cluster class with children and similarity between children
"""
class mycluster:
    def __init__(self, vec=None, children=None, id=None):
        # for drawing picture of clusters
        self.children = children
        # feature vector
        self.vec = vec
        #  id label for locating label
        self.id = id


"""
@ param cluster a and b for comparing, similarity_dic and z3_api
@ return similarity value
@ involve compute similarity between clusters (the first one)
"""
def compute_sim_cluster(cluster_a, cluster_b, similarity_dic, z3_api):

    #  if has record in dictory, then use dictory
    if similarity_dic.get((cluster_b.id, cluster_a.id)) is not None:
        return similarity_dic.get((cluster_b.id, cluster_a.id))

    # compare cdg_list of entity
    if cluster_a.id >= 0 and cluster_b.id >= 0:
        return z3_api.judge_equality_for_statments(cluster_a.vec, cluster_b.vec)

    # first cluster (children)
    if cluster_a.id < 0:
        # translation
        similarity = compute_sim_cluster(cluster_a.children[0], cluster_b, similarity_dic, z3_api)
        return similarity

    # second cluster (children)
    if cluster_b.id < 0:
        # translation
        similarity = compute_sim_cluster(cluster_a, cluster_b.children[0], similarity_dic, z3_api)
        return similarity

"""
@param: cdg_lists(entiry vectors) and z3 api
@return cluster index for each entity
@involve: cluster entities based on similarity
"""
def cluster_record(feature_lists, z3_api):
    # initialize the custers to consist of each entity
    myclusters = [mycluster(children=[], vec=feature_lists[i], id=i) for i in range(len(feature_lists))]
    currentclusted = -1
    similarity_dic = {}

    # stop clustering based on culster number ( == 1)
    while len(myclusters) != 0:

        similarity = 0
        flag = None
        # traverse cluster a and cluster b in clusters
        myclusters_len = len(myclusters)
        for i in range(myclusters_len - 1):
            for j in range(i + 1, myclusters_len):
                # compute similaritys if no record in dictory of similaritys
                if similarity_dic.get((myclusters[i].id, myclusters[j].id)) is None:

                    # compute similaritys by calling computeSim on (vector a, vector b)
                    similarity_dic[(myclusters[i].id, myclusters[j].id)] =\
                        compute_sim_cluster(myclusters[i], myclusters[j], similarity_dic, z3_api)
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
        else:
            # combine the two clusters
            mycluster1, mycluster2 = flag
            # create new bicluster(cluster id is minus number)
            new_mycluster = mycluster(children=[], id=currentclusted)
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
            print len(myclusters)

    # compute cluster_lists based on clusters and cluster number
    cluster_lists = [0 for i in range(len(feature_lists))]
    class_lists = {}
    index = 0
    for now_cluster in myclusters:
        if now_cluster.id < 0:
            # add first children into class lists
            class_lists[now_cluster.children[0].id] = len(now_cluster.children)
            # traverse children
            for child in now_cluster.children:
                cluster_lists[child.id] = index
        else:
            class_lists[now_cluster.id] = 1
            cluster_lists[now_cluster.id] = index
        index += 1

    return cluster_lists, class_lists

"""
@ param
@ return nothing
@ involve read from repos analysis records and write cluster info back
"""
def cluster():

    # initialize read file
    analyze_file = file(my_constant.ANALYZE_REPOS_JOERN_FILE_NAME, 'rb')
    # analyze_file = file('temp.csv', 'rb')
    records = csv.reader(analyze_file)
    # initialize write file
    cluster_file = file(my_constant.CLUSTER_REPOS_FILE_NAME, 'wb')
    # cluster_file = file('temp-cluster.csv', 'wb')
    cluster_file_writer = csv.writer(cluster_file)
    cluster_file_writer.writerow(my_constant.CLUSTER_REPOS_TITLE)
    # initialize class write file
    class_file = file(my_constant.ANALYZE_REPOS_CLASS_FILE_NAME, 'wb')
    class_file_writer = csv.writer(class_file)
    class_file_writer.writerow(my_constant.ANALYZE_REPOS_CLASS_TITLE)

    feature_lists = []
    # traverse the fetch csv file to record cond_lists of each log statement to cdg_lists
    z3_api = Z3_api()
    index = 0
    for record in islice(records, 1, None):  # remove the table title
        # get cdg z3 feature
        cdg_feature = json.loads(record[my_constant.ANALYZE_REPOS_CDG_FEATURE])
        # cdg_feature = json.loads(record[0])
        cdg_z3_feature = z3_api.get_infix_for_postfix(cdg_feature)
        print 'have processed record %d' %(index)
        index += 1
        feature_lists.append(cdg_z3_feature)

    # cluster log statement based on cdg_list and ddg_list
    cluster_lists, class_lists = cluster_record(feature_lists, z3_api)
    # record cluster index of each log statement
    analyze_file.close()

    # write result back
    analyze_file = file(my_constant.ANALYZE_REPOS_JOERN_FILE_NAME, 'rb')
    # analyze_file = file('temp.csv', 'rb')
    records = csv.reader(analyze_file)
    index = 0
    for record in islice(records, 1, None):
        record += [feature_lists[index], cluster_lists[index]]
        cluster_file_writer.writerow(record)
        if class_lists.has_key(index):
            class_file_writer.writerow(record + [class_lists[index]])
        index += 1

    # myUtil.dumpSimilarityDic(similarity_dict)
    # close files
    cluster_file.close()
    class_file.close()
    analyze_file.close()

"""
main function
"""
if __name__ == "__main__":

    cluster()