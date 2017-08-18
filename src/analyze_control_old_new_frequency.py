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
import block
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
def compute_sim_cluster(cluster_a, cluster_b, similarity_dic):

    #  if has record in dictory, then use dictory
    if similarity_dic.get((cluster_b.id, cluster_a.id)) is not None:
        return similarity_dic.get((cluster_b.id, cluster_a.id))

    # compare cdg_list of entity
    if cluster_a.id >= 0 and cluster_b.id >= 0:
       return myUtil.compute_similarity(cluster_a.vec, cluster_b.vec)

    # first cluster (children)
    if cluster_a.id < 0:
        # translation
        similarity = compute_sim_cluster(cluster_a.children[0], cluster_b, similarity_dic)
        return similarity

    # second cluster (children)
    if cluster_b.id < 0:
        # translation
        similarity = compute_sim_cluster(cluster_a, cluster_b.children[0], similarity_dic)
        return similarity

"""
@param: cdg_lists(entiry vectors), cluster_similarity = 0.90
@return cluster index for each entity
@involve: cluster entities based on similarity
"""
def cluster_record(feature_lists, cluster_similarity = 0.95):
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
                        compute_sim_cluster(myclusters[i], myclusters[j], similarity_dic)
                    # record symmetrical record
                    similarity_dic[(myclusters[j].id, myclusters[i].id)] =\
                                similarity_dic[(myclusters[i].id, myclusters[j].id)]

                #  fetch the similarity
                similarity = similarity_dic[(myclusters[i].id, myclusters[j].id)]
                # find cluster pair with maxest similarity and flag them
                if similarity == 1:
                    flag = (i, j)
                    break
            if similarity == 1:
                   break
        if similarity != 1:
            break
        else:
            # combine the two clusters
            mycluster1, mycluster2 = flag
            # create new bicluster(cluster id is minus number)
            new_mycluster = mycluster(children=[], similarity=similarity, id=currentclusted)
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
def cluster():

    # initialize read file
    analyze_control = file(my_constant.ANALYZE_OLD_NEW_JOERN_FILE_NAME, 'rb')
    records = csv.reader(analyze_control)
    # initialize write file
    cluster_control = file(my_constant.STATISTICS_OLD_NEW_FILE_NAME, 'wb')
    cluster_control_writer = csv.writer(cluster_control)
    cluster_control_writer.writerow(my_constant.STATISTICS_OLD_NEW_TITLE)

    feature_lists = []
    old_log_types = []
    old_log_times = []
    gumtree = Gumtree()
    gh = Github(login='993273596@qq.com', password='nx153156', user=my_constant.USER, repo=my_constant.REPOS)
    # traverse the fetch csv file to record cond_lists of each log statement to cdg_lists
    index = 0
    for record in islice(records, 1, None):  # remove the table title
        # get old and new log feature
        old_log_file = record[my_constant.ANALYZE_OLD_NEW_OLD_LOG_FILE]
        gumtree.set_file(old_log_file)
        old_log_feature = gumtree.get_block_feature()
        old_log_types.append(gumtree.get_block_type())
        old_log_times.append(get_time_for_sha(record[my_constant.ANALYZE_OLD_NEW_SHA], gh))
        new_log_file = record[my_constant.ANALYZE_OLD_NEW_NEW_LOG_FILE]
        gumtree.set_file(new_log_file)
        new_log_feature = gumtree.get_block_feature()

        feature_lists.append(old_log_feature + new_log_feature)
        print 'now processing %d file' %(index)
        index += 1
    
    # cluster log statement based on cdg_list and ddg_list
    cluster_lists = cluster_record(feature_lists)
    # record cluster index of each log statement
    analyze_control.close()
    analyze_control = file(my_constant.ANALYZE_OLD_NEW_JOERN_FILE_NAME, 'rb')
    records = csv.reader(analyze_control)
    index = 0
    for record in islice(records, 1, None):
        record = record + [old_log_types[index]] + old_log_times[index] + [cluster_lists[index]]
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

    cluster()