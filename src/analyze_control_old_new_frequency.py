#-*-coding: utf-8 -*-
import csv
import json
from itertools import islice
import myUtil
import my_constant
from gumtree_api import Gumtree

"""
@ param old log and new log, old block feature and repos block feature and gumtree
@ return  bool about whether has matched
@ involve decide whether match or not, <- block feature enjoy high similarity and match log
"""
def is_match(old_new_info, repos_info, gumtree):
    old_new_block_feature = old_new_info[0]
    old_log_file = old_new_info[1]
    new_log_file = old_new_info[2]
    repos_block_feature = repos_info[0]
    repos_log_file = repos_info[1]
    if myUtil.compute_similarity(old_new_block_feature, repos_block_feature) > 0.999:
        # return gumtree.is_match_with_edit(old_log_file, new_log_file, repos_log_file)
        return gumtree.is_match(old_log_file, repos_log_file)
    else:
        return False

"""
@ param
@ return ...
@ involve compute the frequency of repeat modification
"""
def compute_frequence():

    # initialize log_patch from given patch analysis result
    frequency = {}
    repetition = {}
    log_file = file(my_constant.ANALYZE_OLD_NEW_FILE_NAME, 'rb')
    records = csv.reader(log_file)
    index = 1
    for record in islice(records, 1, None):
        old_log = record[my_constant.ANALYZE_OLD_NEW_OLD_LOG]
        new_log = record[my_constant.ANALYZE_OLD_NEW_NEW_LOG]
        old_loc = record[my_constant.ANALYZE_OLD_NEW_OLD_LOC]
        filename = record[my_constant.ANALYZE_OLD_NEW_FILE]
        if frequency.has_key((old_log, new_log)):
            # no repetition count of commit
            if not repetition.has_key((filename, old_loc, old_log, new_log)):
                frequency[(old_log, new_log)].append(index)
                repetition[(filename, old_loc, old_log, new_log)] = 1
        else:
            frequency[(old_log, new_log)] = [index]
        index += 1
  
    # close files
    log_file.close()
    # seek clones in repos of context for each log update in patch

    # write back into file
    frequency_file = file(my_constant.STATISTICS_OLD_NEW_FILE_NAME, 'wb')
    frequency_writer = csv.writer(frequency_file)
    frequency_writer.writerow(my_constant.STATISTICS_OLD_NEW_TITLE)

    for key in frequency:
        frequency_writer.writerow([key[0], key[1], json.dumps(frequency[key]), len(frequency[key])])
    frequency_file.close()


"""
main function
"""
if __name__ == "__main__":

    compute_frequence()
    # list_a = [[["!", "struct group_of_users *"]], [["strstr", "char *", "\"group \"", "char *", "=="]]]
    # list_b = [[["!", "struct user *"]], [["strstr", "char *", "\"user \"", "char *", "=="]]]
    # print compute_context_similarity(list_a, list_b, {})