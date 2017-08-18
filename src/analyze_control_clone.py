#-*-coding: utf-8 -*-
import csv
import json
from itertools import islice
import myUtil
import my_constant
from gumtree_api import Gumtree
from z3_api import Z3_api

"""
@ param old log and new log, old block feature and repos block feature and gumtree
@ return  bool about whether has matched
@ involve decide whether match or not, <- block feature enjoy high similarity and match log
"""
def is_match(old_new_info, repos_info, gumtree, z3_api):
    # old_new_block_feature = old_new_info[0]
    old_new_cdg_z3_feature = old_new_info[0]
    old_log_file = old_new_info[1]
    new_log_file = old_new_info[2]
    # repos_block_feature = repos_info[0]
    repos_cdg_z3_feature = repos_info[0]
    repos_log_file = repos_info[1]
    # if myUtil.compute_similarity(old_new_block_feature, repos_block_feature) > 0.999:
    if z3_api.judge_equality_for_statments(old_new_cdg_z3_feature, repos_cdg_z3_feature):
        return True
        # return gumtree.is_match_with_edit(old_log_file, new_log_file, repos_log_file)
        # return gumtree.is_match(old_log_file, repos_log_file)
    else:
        return False

"""
@ param
@ return ...
@ involve get clone of context in repos for each log updates
"""
def seek_clone():
    z3_api = Z3_api()

    # initialize log_patch from given patch analysis result
    old_new_infos = []
    old_new_record_info = []
    old_new_file = file(my_constant.ANALYZE_OLD_NEW_JOERN_FILE_NAME, 'rb')
    old_new_records = csv.reader(old_new_file)
    for old_new_record in islice(old_new_records, 1, None):
        # old_new_block_feature = json.loads(old_new_record[my_constant.ANALYZE_OLD_NEW_OLD_BLOCK_FEATURE])
        old_new_cdg_feature = json.loads(old_new_record[my_constant.ANALYZE_OLD_NEW_OLD_CDG_FEATURE])
        old_new_cdg_z3_feature = z3_api.get_infix_for_postfix(old_new_cdg_feature)
        old_new_old_log_file = old_new_record[my_constant.ANALYZE_OLD_NEW_OLD_LOG_FILE]
        old_new_new_log_file = old_new_record[my_constant.ANALYZE_OLD_NEW_NEW_LOG_FILE]
        old_new_infos.append([old_new_cdg_z3_feature, old_new_old_log_file, old_new_new_log_file])
        old_new_record_info.append(old_new_record)
    # initialize log_repos from given repos analysis result
    repos_infos = []
    repos_record_info = []
    repos_file = file(my_constant.ANALYZE_REPOS_CLASS_FILE_NAME, 'rb')
    repos_records = csv.reader(repos_file)
    for repos_record in islice(repos_records, 1, None):
        # repos_block_feature = json.loads(repos_record[my_constant.ANALYZE_REPOS_BLOCK_FEATURE])
        repos_cdg_feature = json.loads(repos_record[my_constant.ANALYZE_REPOS_CDG_FEATURE])
        repos_cdg_z3_feature = z3_api.get_infix_for_postfix(repos_cdg_feature)
        repos_log_file = repos_record[my_constant.ANALYZE_REPOS_LOG_FILE]
        repos_infos.append([repos_cdg_z3_feature, repos_log_file])
        repos_record_info.append([repos_record[my_constant.ANALYZE_REPOS_CLASS_INDEX], repos_record[my_constant.ANALYZE_REPOS_CLASS_SIZE]])
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
    for old_new_info in old_new_infos:
        index_repos = 0
        clone_count = 0
        # traverse repos to find similar contexts
        for repos_info in repos_infos:
            # print "now analyze the no.%d old new log; %d repos log"\
            #      %(index_old_new, index_repos)
            if is_match(old_new_info, repos_info, gumtree, z3_api):
                clone_writer.writerow(old_new_record_info[index_old_new] + repos_record_info[index_repos])
                clone_count += int(repos_record_info[index_repos][1])
                # clone_count += 1
                clone_num_writer.writerow([clone_count])
                print "now analyze the no.%d patch; the clone count is %d"\
                                %(index_old_new, clone_count)
                break
            index_repos += 1
        # print "now analyze the no.%d patch; the clone count is %d"\
        #          %(index_old_new, clone_count)
        # clone_num_writer.writerow([clone_count])
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