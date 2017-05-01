#-*-coding: utf-8 -*-
import csv
import sys
import re
import commands
import json
from itertools import islice
from PIL import Image, ImageDraw


"""
@param: cluster
@return int height
@caller drawnode
@callee self
@involve: get height of the cluster with children
"""
def getheight(clust):
    if clust.left is None and clust.right is None:
        return 1
    return getheight(clust.left) + getheight(clust.right)

"""
@param: cluster
@return int depth
@caller draw_dendrogram
@callee self
@involve: get depth of the cluster with children
"""
def getdepth(clust):
    if clust.left is None and clust.right is None:
        return 0
    return max(getdepth(clust.left), getdepth(clust.right)) + clust.similarity

"""
@param: cluster, labels, img name to save
@return none
@caller main
@callee drawnode, getdepth, getheight
@involve: draw clusters with labels and save to given image file
"""
def draw_dendrogram(clust, labels, jpeg='clusters.jpg'):
    # set hight according to cluster height (number of entity)
    h = getheight(clust) * 20
    w = 5000
    # get depth of cluster(total similarity)
    depth = max(getdepth(clust), 1)

    scaling = float(w-150) / depth

    img = Image.new('RGB', (w, h), (255, 255, 255))
    draw = ImageDraw.Draw(img)
    draw.line((0, h/2, 10, h/2), fill=(255, 0, 0))
    # draw the cluster from top by calling drawnode (center in h)
    drawnode(draw, clust, 10, (h/2), scaling, labels)
    img.save(jpeg, 'JPEG')

"""
@param: draw, cluster, x(w), y(h), scaling, labels
@return int depth
@caller draw_dendrogram
@callee self
@involve: draw cluster by coping with children
"""
def drawnode(draw, clust, x, y, scaling, labels):
    if clust.id < 0:
        h1 = getheight(clust.left) * 20
        h2 = getheight(clust.right) * 20

        top = y - (h1+h2)/2
        bottom = y + (h1+h2)/2
        #line length by similarity multiply scaling
        ll = clust.similarity * scaling

        # left line
        draw.line((x, top+h1/2, x, bottom-h2/2), fill=(255, 0, 0))
        # top line
        draw.line((x, top+h1/2, x+ll, top+h1/2), fill=(255, 0, 0))
        # bottom line
        draw.line((x, bottom-h2/2, x+ll, bottom-h2/2), fill=(255, 0, 0))
        # left children
        drawnode(draw, clust.left, x+ll, top+h1/2, scaling, labels)
        # right children
        drawnode(draw, clust.right, x+ll, bottom-h2/2, scaling, labels)
    else:
        # draw label
        draw.text((x+5, y-7), labels[clust.id], (0, 0, 0))

"""
@ param  string a and b to compute
@ return lenth of common substring / min length
@ callee ...
@ caller computeSim ..
@ involve compute the longgest common string (continuous) of two string
"""
def longestCommonStrBase(string_a, string_b):

    # none in middle of list can be ignore
    if string_a is None or string_b is None:
        return 1.0

    # if just one element, compare directly
    len_a = len(string_a)
    len_b = len(string_b)
    if len_a == 1 or  len_b == 1:
        return float(string_a[0] == string_b[0])

    # length of a and b
    len_a += 1
    len_b += 1

    len_common = 0
    # index_end = 0
    memory = [[0 for col in range(len_b)] for row in range(len_a)]
    for i in range(1, len_a):
        for j in range(1, len_b):
            # update len_common with history
            if string_a[i - 1] == string_b[j-1]:
                memory[i][j] = memory[i-1][j-1] + 1
                len_common = max(memory[i][j], len_common)
            else:
                memory[i][j] = 0

    # simlarity value with common length / min length (0, 1)
    return float(len_common)/min(len_a, len_b)


"""
@ param  cond_list of a and b to compute
@ return lenth of common substring / min length
@ callee ...
@ caller computeSim ..
@ involve compute the longgest common string (continuous) of two cond_list
"""
def longestCommonStr(cond_list_a, cond_list_b):

    # if just one element, then compare that
    len_a = len(cond_list_a)
    len_b = len(cond_list_b)
    if len_a == 1 or len_b == 1:
        # return float(longestCommonStrBase(cond_list_a[0], cond_list_b[0]) > 0.5)
        return float(cond_list_a[0] == cond_list_b[0])
    # length of a and b
    len_a += 1
    len_b += 1

    len_common = 0
    # index_end = 0
    memory = [[0 for col in range(len_b)] for row in range(len_a)]
    for i in range(1, len_a):
        for j in range(1, len_b):
            # update len_common with history
            if cond_list_a[i - 1] == cond_list_b[j-1]:
            # if commmon substring length of two string is larger than 0.7 -> same
            # if longestCommonStrBase(cond_list_a[i - 1], cond_list_b[j-1]) > 0.5:
                memory[i][j] = memory[i-1][j-1] + 1
                len_common = max(memory[i][j], len_common)
            else:
                memory[i][j] = 0

    # simlarity value with common length / min length (0, 1)
    return float(len_common)/min(len_a, len_b)


"""
@ param cond_list a and b for comparing
@ return similarity value
@ callee longestCommonSeq
@ caller computeSimForCluster ..
@ involve compute similarity between cond_lists
"""
def computeSim(cond_lists_a, cond_lists_b):
    len_a = len(cond_lists_a)
    len_b = len(cond_lists_b)

    # do not deal with 0 exception at this period
    if len_a == 0 or len_b == 0:
        return 0

    # record the similarity matrix
    memory = [[0 for col in range(len_b)] for row in range(len_a)]
    # similarity between a and b
    sim_value_a_b = 0
    for index_a in range(len_a):
        # max in given row
        best_sim_value_a = 0
        for index_b in range(len_b):
            # # various flowLabel --> sim_value = 0
            # sim_value = 0
            # if cond_list_a[1] == cond_list_b[1]:
            # compute similarity between cond_list_a[0] and cond_list_b[0]
            memory[index_a][index_b] = longestCommonStr(cond_lists_a[index_a][0], cond_lists_b[index_b][0])
            best_sim_value_a = max(memory[index_a][index_b], best_sim_value_a)
        # summary total similarity between a and b
        sim_value_a_b += best_sim_value_a
    sim_value_a_b = sim_value_a_b / len_a # (0, 1)

    # similarity between b and a
    sim_value_b_a = 0
    for index_b in range(len_b):
        # max in given column
        best_sim_value_b = max([row[index_b] for row in memory])
        # summary total similarity between a and b
        sim_value_b_a += best_sim_value_b
    sim_value_b_a = sim_value_b_a / len_b # (0, 1)

    return (sim_value_b_a + sim_value_a_b) / 2 # (0, 1)

"""
@param vec, left, right, similarity, id
@return new cluster
@involve cluster class with two children and similarity between children
"""
class mycluster:
    def __init__(self, vec=None, left=None, right=None, similarity=0.0, id=None):
        # for drawing picture of clusters
        self.left = left
        self.right = right
        # feature vector
        self.vec = vec
        #  id label for locating label
        self.id = id
        self.similarity = similarity


"""
@ param cluster a and b for comparing
@ return similarity value
@ callee computeSim(cond_list_a, cond_list_b); self
@ caller cluster_record ..
@ involve compute similarity between clusters (the least similar cond_list pairs)
"""
def computeSimForCluster(cluster_a, cluster_b, similarity = 1):

    #  if has record in dictory, then use dictory
    if similarity_dic.get((cluster_a.id, cluster_b.id)) is not None:
        return min(similarity_dic.get((cluster_a.id, cluster_b.id)), similarity)

    # compare cdg_list of entity
    if cluster_a.id >= 0 and cluster_b.id >= 0:
        similarity = min(computeSim(cluster_a.vec, cluster_b.vec), similarity)
        return similarity

    # first cluster (left and right children)
    if cluster_a.id < 0:
        similarity = min(computeSimForCluster(cluster_a.left, cluster_b, similarity), similarity)
        similarity = min(computeSimForCluster(cluster_a.right, cluster_b, similarity), similarity)
        return similarity

    # second cluster (left and right children)
    if cluster_b.id < 0:
        similarity = min(computeSimForCluster(cluster_a, cluster_b.left, similarity), similarity)
        similarity = min(computeSimForCluster(cluster_a, cluster_b.right, similarity), similarity)
        return similarity

"""
@ param myclusters and cluster_lists and index of mycluster
@ return cluster_lists
@ callee  self
@ caller cluster_record ..
@ involve compute cluster index (cluster_lists) for each entity according to myclusters(the bi cluster tree)
"""
def computeClusterLists(mycluster, cluster_lists, index):

    # if is entity, update its cluster index in cluster_lists
    if mycluster.id >= 0:
        cluster_lists[mycluster.id] = index
        return cluster_lists

    if mycluster.id < 0:
        # left children
        cluster_lists = computeClusterLists(mycluster.left, cluster_lists, index)
        # right children
        cluster_lists = computeClusterLists(mycluster.right, cluster_lists, index)
        return cluster_lists


"""
@param: cdg_lists(entiry vectors), label_lists(labels)
@return cluster index for each entity
@caller cluster
@callee computeSimForCluster
@involve: cluster entities based on similarity
"""
def cluster_record(cdg_lists, label_lists):
    # initialize the custers to consist of each entity
    myclusters = [mycluster(vec=cdg_lists[i], id=i) for i in range(len(cdg_lists))]
    flag = None
    currentclusted = -1

    # stop clustering based on culster number ( == 1)
    while len(myclusters) > 1:
        # the miniest similarity to merge two cluster
        max_sim = -1

        # traverse cluster a and cluster b in clusters
        myclusters_len = len(myclusters)
        for i in range(myclusters_len - 1):
            for j in range(i + 1, myclusters_len):

                # compute similaritys if no record in dictory of similaritys
                if similarity_dic.get((myclusters[i].id, myclusters[j].id)) is None:

                    # compute similaritys by calling computeSim on (vector a, vector b)
                    similarity_dic[(myclusters[i].id, myclusters[j].id)] =\
                                 computeSimForCluster(myclusters[i], myclusters[j])
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
        if max_sim < cluster_similarity:
            break
        # combine the two clusters
        mycluster1, mycluster2 = flag
        # create new bicluster(cluster id is minus number)
        new_mycluster = mycluster(left=myclusters[mycluster1], right=myclusters[mycluster2], similarity=max_sim, id=currentclusted)
        currentclusted -= 1
        # remove old cluster from the clusters
        # have not destroy it
        del myclusters[mycluster2]
        del myclusters[mycluster1]
        myclusters.append(new_mycluster)

    # draw the cluster result into jpg file
    # draw_dendrogram(myclusters, label_lists, jpeg='data/cdg_cluster.jpg')

    # compute cluster_lists based on clusters and cluster number
    cluster_lists = [0 for i in range(len(cdg_lists))]
    index = 0
    for now_cluster in myclusters:
        cluster_lists = computeClusterLists(now_cluster, cluster_lists, index)
        index += 1
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
    cluster_control_writer.writerow(['commit_message', 'file_name', 'change_type', 'log_node', \
        'cdg_nodes', 'neighbor_nodes', 'condition_lists', 'store_name', 'log_loc', 'cluster_index'])

    cdg_lists = []
    # traverse the fetch csv file to record cond_lists of each log statement to cdg_lists
    label_lists = []
    for record in islice(records, 1, None):  # remove the table title
        # store cond_lists(index 6)
        cond_lists = json.loads(record[6])
        cdg_lists.append(cond_lists)
        # label for each entity [log node](index 3)
        label_lists.append(record[3])

    # cluster log statement based on cdg_lists and cdg_nodes(label)
    # cluster_lists = cdg_lists
    cluster_lists = cluster_record(cdg_lists, label_lists)
    # record cluster index of each log statement
    analyze_control.close()
    analyze_control = file('data/analyz_joern_' + user + '_' + repos + '.csv', 'rb')
    records = csv.reader(analyze_control)
    index = 0
    for record in islice(records, 1, None):
        record.append(cluster_lists[index])
        cluster_control_writer.writerow(record)
        index += 1

    # close files
    cluster_control.close()
    analyze_control.close()

    similarity_control = file('data/similarity_' + user + '_' + repos + '.csv', 'wb')
    similarity_control_writer = csv.writer(similarity_control)
    similarity_control_writer.writerow(["left", "right", "similarity"])
    # dump similarity
    for pair, similarity in similarity_dic.items():
        if pair[0] >= 0 and pair[1] >= 0:
            similarity_control_writer.writerow([pair[0], pair[1], similarity])
    similarity_control.close()

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

# dictory for clustering
similarity_dic = {}
cluster_similarity = 0.5
cluster( user, repos)