#-*-coding: utf-8 -*-
import csv
import json
from itertools import islice
import block
import myUtil
import my_constant
from gumtree_api import Gumtree

"""
@ param user and repos
@ return ...
@ caller main
@ callee compute_context_similarity
@ involve get clone of context in repos for each log updates
"""
def seek_clone():

    # initialize log_patch from given patch analysis result
    old_new_logs = []
    old_new_record_info = []
    old_new_file = file(my_constant.ANALYZE_OLD_NEW_FILE_NAME, 'rb')
    old_new_records = csv.reader(old_new_file)
    for old_new_record in islice(old_new_records, 1, None):
        old_new_logs.append(old_new_record[my_constant.ANALYZE_OLD_NEW_LOG_FILE])
        old_new_record_info.append(old_new_record)
    # initialize log_repos from given repos analysis result
    repos_logs = []
    repos_record_info = []
    repos_file = file(my_constant.ANALYZE_REPOS_FILE_NAME, 'rb')
    repos_records = csv.reader(repos_file)
    for repos_record in islice(repos_records, 1, None):
        repos_logs.append(repos_record[my_constant.ANALYZE_REPOS_LOG_FILE])
        repos_record_info.append(repos_record)
    # close files
    old_new_file.close()
    repos_file.close()

    # seek clones in repos of context for each log update in patch

    # write back into file
    clone_file = file(my_constant.ANALYZE_CLONE_FILE_NAME, 'wb')
    clone_writer = csv.writer(clone_file)
    clone_writer.writerow(my_constant.ANALYZE_CLONE_TITLE)
    clone_num_file = file(my_constant.STATISTICS_CLONE_NUM_FILE_NAME, 'wb')
    clone_num_writer = csv.writer(clone_num_file)
    clone_num_writer.writerow(['count'])

    gumtree = Gumtree()
    index_old_new = 0
    for old_new_log in old_new_logs:
        index_repos = 0
        clone_count = 0
        # traverse repos to find similar contexts
        for repos_log in repos_logs:
            print "now analyze the no.%d old new log; %d repos log"\
                 %(index_old_new, index_repos)
            if gumtree.is_match(old_new_log, repos_log):
                clone_writer.writerow(old_new_record_info[index_old_new] + repos_record_info[index_repos])
                clone_count += 1
            index_repos += 1
        print "now analyze the no.%d patch; the clone count is %d"\
                 %(index_old_new, clone_count)
        clone_num_writer.writerow([clone_count])
        index_old_new += 1

    clone_file.close()
    clone_num_file.close()
    gumtree.close()


"""
main function
"""
if __name__ == "__main__":

    seek_clone()
    # list_a = [[["!", "struct group_of_users *"]], [["strstr", "char *", "\"group \"", "char *", "=="]]]
    # list_b = [[["!", "struct user *"]], [["strstr", "char *", "\"user \"", "char *", "=="]]]
    # print compute_context_similarity(list_a, list_b, {})