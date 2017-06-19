#-*-coding: utf-8 -*-
import csv
import json
from itertools import islice
import block
import myUtil
import my_constant

"""
@ param user and repos
@ return ...
@ caller main
@ callee compute_context_similarity
@ involve get clone of context in repos for each log updates
"""
def seek_clone():

    # initialize log_patch from given patch analysis result
    log_patch = []
    context_patch = []
    patch_file_name = my_constant.ANALYZE_OLD_NEW_FILE_NAME
    patch_file = file(patch_file_name, 'rb')
    patch_records = csv.reader(patch_file)
    for patch_record in islice(patch_records, 1, None):
        # old_context_list index (add commit sha)
        context_patch.append(json.loads(patch_record[my_constant.ANALYZE_OLD_NEW_OLD_BLOCK_VECTOR]))
        # ddg_patch.append(json.loads(patch_record[my_constant.ANALYZE_OLD_NEW_OLD_DDG]))
        log_patch.append(patch_record)
    # initialize log_repos from given repos analysis result
    log_repos = []
    context_repos = []
    repos_file_name = my_constant.ANALYZE_REPOS_FILE_NAME
    repos_file = file(repos_file_name, 'rb')
    repos_records = csv.reader(repos_file)
    for repos_record in islice(repos_records, 1, None):
        # context_list index
        context_repos.append(json.loads(repos_record[my_constant.ANALYZE_REPOS_VECTOR]))
        # ddg_repos.append(json.loads(repos_record[my_constant.ANALYZE_REPOS_DDG]))
        log_repos.append(repos_record)

    # close files
    patch_file.close()
    repos_file.close()

    # seek clones in repos of context for each log update in patch

    # write back into file
    clone_csv = file(my_constant.ANALYZE_CLONE_FILE_NAME, 'wb')
    clone_csv_writer = csv.writer(clone_csv)
    clone_csv_writer.writerow(my_constant.ANALYZE_CLONE_TITLE)
    clone_num_csv = file(my_constant.STATISTICS_CLONE_NUM_FILE_NAME, 'wb')
    clone_num_csv_writer = csv.writer(clone_num_csv)
    clone_num_csv_writer.writerow(['count'])

    index_patch = 0
    for patch in context_patch:
        index_repos = 0
        clone_count = 0
        # traverse repos to find similar contexts
        for reposi in context_repos:
            if block.compute_similarity(patch, reposi) >= 0.99:
                clone_csv_writer.writerow(log_patch[index_patch] + log_repos[index_repos])
                clone_count += 1
            index_repos += 1
        print "now analyze the no.%d patch; the clone count is %d"\
                 %(index_patch, clone_count)
        clone_num_csv_writer.writerow([clone_count])
        index_patch += 1

    clone_csv.close()
    clone_num_csv.close()


"""
main function
"""
if __name__ == "__main__":

    seek_clone()
    # list_a = [[["!", "struct group_of_users *"]], [["strstr", "char *", "\"group \"", "char *", "=="]]]
    # list_b = [[["!", "struct user *"]], [["strstr", "char *", "\"user \"", "char *", "=="]]]
    # print compute_context_similarity(list_a, list_b, {})