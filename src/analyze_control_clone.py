#-*-coding: utf-8 -*-
import myUtil
import csv
import json
import re
from itertools import islice
from joern.all import JoernSteps

"""
@ param  cond_list of a and b to compute, func_similarity_dic
@ return lenth of common substring / min length
@ callee ...
@ caller compute_context_similarity ..
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
@ callee longestCommonStr
@ caller seek_clone ..
@ involve compute similarity between two context lists (subset)
"""
def compute_context_similarity(cond_lists_a, cond_lists_b, func_similarity_dic):
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

    # return float(len_common)*2 / (len_a + len_b) # (0, 1)
    return float(len_common == min(len_a, len_b))

"""
@ param user and repos
@ return ...
@ caller main
@ callee compute_context_similarity
@ involve get clone of context in repos for each log updates
"""
def seek_clone(user, repos):

    # initialize log_patch from given patch analysis result
    log_patch = []
    context_patch = []
    patch_file_name = 'data/fetch/' + user + '_' + repos + '_old_new_analyze.csv'
    patch_file = file(patch_file_name, 'rb')
    patch_records = csv.reader(patch_file)
    for patch_record in islice(patch_records, 1, None):
        # old_context_list 9 (add commit sha)
        context_patch.append(json.loads(patch_record[9]))
        log_patch.append(patch_record)
    # initialize log_repos from given repos analysis result
    log_repos = []
    context_repos = []
    repos_file_name = 'data/fetch/' + user + '_' + repos + '_repos_analyze.csv'
    repos_file = file(repos_file_name, 'rb')
    repos_records = csv.reader(repos_file)
    for repos_record in islice(repos_records, 1, None):
        # context_list 3
        context_repos.append(json.loads(repos_record[3]))
        log_repos.append(repos_record)

    # close files
    patch_file.close()
    repos_file.close()

    # initialize function similarity dictionary
    func_similarity_file_name = 'data/fetch/' + user + '_' + repos + '_func_similarity.csv'
    func_similarity_dic = myUtil.getFunctionSimilarityDic(True, func_similarity_file_name)

    # seek clones in repos of context for each log update in patch
    clone_patch_repos = []
    index_patch = 0
    for patch in context_patch:
        index_repos = 0
        clone_count = 0
        # traverse repos to find similar contexts
        for reposi in context_repos:
            if compute_context_similarity(patch, reposi, func_similarity_dic) == 1:
                clone_patch_repos.append(log_patch[index_patch] + log_repos[index_repos])
                clone_count += 1
            index_repos += 1
        print "now analyze the no.%d patch; the clone count is %d"\
                 %(index_patch, clone_count)
        index_patch += 1

    # write back into file
    out_csv = file('data/fetch/' + user + '_' + repos + '_seek_clone.csv', 'wb')
    out_csv_writer = csv.writer(out_csv)
    out_csv_writer.writerow(['commit_sha', 'commit_message', 'file_name',\
        'change_type', 'log_node', \
        'old_log_loc', 'old_store_name', 'new_log_loc', 'new_store_name', \
        'old_context_list', 'new_context_list', 'ddg_list', 'static_list', \
        'clone_log', 'clone_location', 'clone_file_name', 'clone_context_list',\
        'clone_ddg_list', 'clone_static_list'])
    for clone in clone_patch_repos:
        out_csv_writer.writerow(clone)
    out_csv.close()


"""
main function
"""
if __name__ == "__main__":
    # several configuration constant: user, repos
    # user = 'mongodb'
    # repos = 'mongo'
    # user = 'opencv'
    # repos = 'opencv'
    user = 'Kitware'
    repos = 'CMake'
    # user = 'llvm-mirror'
    # repos = 'clang'
    # user = 'torvalds'
    # repos = 'linux'

    seek_clone(user, repos)