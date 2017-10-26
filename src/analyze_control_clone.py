#-*-coding: utf-8 -*-
import csv
import json
from itertools import islice
import my_util
import my_constant
import cluster_api

def is_match_for_insert_rule(rule_feature, function_feature):
    """
    @ param rule feature(check, variable) and function feature(calls, types)\n
    @ return true if match\n
    @ involve validate that any element in rule feature must exist in function\n
    """
    check = rule_feature[0]
    variable = rule_feature[1]
    calls = function_feature[0]
    types = function_feature[1]
    # validate whether any one in check or variable is in calls and types
    rule_infos = check + variable
    function_info = calls + types
    for info in rule_infos:
        if not info in function_info:
            return False
    return True

def is_match_for_modify_rule(rule_feature, repos_log_feature):
    """
    @ param rule feature(check, variable) and repos log feature(check, variable)\n
    @ return true if match\n
    @ involve validate that check and variable info must be exactly same\n
    """
    return rule_feature == repos_log_feature

def seek_clone():
    """
    @ param nothing \n
    @ return nothing \n
    @ involve match rule class with repos log class and function\n
    """
    # initiate csv reader file(rule class, repos log class, function class)
    rule_file = file(my_constant.CLASS_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME, 'rb')
    rule_records = csv.reader(rule_file)
    repos_log_class_file = file(my_constant.CLASS_REPOS_LOG_FILE_NAME, 'rb')
    repos_log_records = csv.reader(repos_log_class_file)
    repos_function_file = file(my_constant.ANALYZE_REPOS_FUNCTION_FILE_NAME, 'rb')
    repos_function_records = csv.reader(repos_function_file)
    # initiate csv writer file(repos log clone and function clone)
    repos_log_clone_file = file(my_constant.ANALYZE_CLONE_LOG_FILE_NAME, 'wb')
    repos_log_clone_writer = csv.writer(repos_log_clone_file)
    repos_log_clone_writer.writerow(my_constant.ANALYZE_CLONE_LOG_TITLE)
    repos_function_clone_file = file(my_constant.ANALYZE_CLONE_FUNCTION_FILE_NAME, 'wb')
    repos_function_clone_writer = csv.writer(repos_function_clone_file)
    repos_function_clone_writer.writerow(my_constant.ANALYZE_CLONE_FUNCTION_TITLE)
    rule_counter = 0
    rule_size = len(rule_records)
    # search clone instance for each rule
    for rule_record in islice(rule_records, 1, None):
        rule_counter += 1
        print 'now processing rule %d/%d, ' %(rule_counter, rule_size) ,
        old_loc = json.loads(rule_record.index(my_constant.CLASS_OLD_NEW_OLD_LOC))
        check = json.loads(rule_record.index(my_constant.CLASS_OLD_NEW_CHECK))
        variable = rule_record.index(my_constant.CLASS_OLD_NEW_VARIABLE)
        rule_feature = [check, variable]
        clone_counter = 0
        # insert rule -> function records
        if old_loc == '-1':
            for repos_function_record in repos_function_records:
                calls = json.loads(repos_function_record.index(my_constant.ANALYZE_REPOS_FUNCTION_CALLS))
                types = json.loads(repos_function_record.index(my_constant.ANALYZE_REPOS_FUNCTION_TYPES))
                if is_match_for_insert_rule(rule_feature, [types, calls]):
                    clone_counter += 1
                    repos_function_clone_writer.writerow(rule_record + repos_function_record)
        # modification -> log records
        else:
            for repos_log_record in repos_log_records:
                log_check = json.loads(repos_log_record.index(my_constant.CLASS_REPOS_LOG_CHECK))
                log_variable = json.loads(repos_log_record.index(my_constant.CLASS_REPOS_LOG_VARIABLE))
                if is_match_for_modify_rule(rule_feature, [log_check, log_variable]):
                    # get real log records from class index
                    analyze_log_records = cluster_api.generate_records_for_class(my_constant.ANALYZE_REPOS_LOG_CLUSTER, repos_log_record[0])
                    for analyze_log_record in analyze_log_records:
                        clone_counter += 1
                        repos_log_clone_writer.writerow(rule_record + analyze_log_record)
                    
        print 'find clone instances %d' %(clone_counter)

    # close file
    rule_file.close()
    repos_log_class_file.close()
    repos_function_file.close()
    repos_function_clone_file.close()
    repos_log_clone_file.close()

"""
main function
"""
if __name__ == "__main__":

    seek_clone()
    # list_a = [[["!", "struct group_of_users *"]], [["strstr", "char *", "\"group \"", "char *", "=="]]]
    # list_b = [[["!", "struct user *"]], [["strstr", "char *", "\"user \"", "char *", "=="]]]
    # print compute_context_similarity(list_a, list_b, {})