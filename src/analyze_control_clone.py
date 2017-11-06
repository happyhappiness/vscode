#-*-coding: utf-8 -*-
import csv
import json
from itertools import islice
import my_util
import my_constant
import cluster_api

def check_given_log_in_function(function_name, check, variable):
    """
    @ param function name, check and variable constaints\n
    @ return true if has that kind of log\n
    @ involve traverse log analysis data and try to find logs statisfying given constraints\n
    """
    log_file = file(my_constant.ANALYZE_REPOS_LOG_FILE_NAME, 'rb')
    log_records = csv.reader(log_file)
    flag_meet_function = False
    for log_record in islice(log_records, 1, None):
        # logs in given function
        if log_record[my_constant.ANALYZE_REPOS_LOG_FUNCTION] == function_name:
            flag_meet_function = True
            # filter with check and variable info
            if check == json.loads(log_record[my_constant.ANALYZE_REPOS_LOG_CHECK])\
                and variable == json.loads(log_record[my_constant.ANALYZE_REPOS_LOG_VARIABLE]):
                log_file.close()
                return True
        # records store by function name, so quit if meet new function name
        elif flag_meet_function:
            log_file.close()
            return False

    log_file.close()
    return False

def check_for_insert_rule(rule_feature, function):
    """
    @ param rule feature(check, variable) and function name\n
    @ return true if need insert log\n
    @ involve check whether there is log that do given check and output given variable, if do, return false\n
    """
    check = rule_feature[0]
    variable = rule_feature[1]
    # has log -> no need
    if check_given_log_in_function(function, check, variable):
        return False
    else:
        return True

def check_for_modify_rule(edit_words, curr_log):
    """
    @ param edit words(old edits and new edits)\n
    @ return true if need edit\n
    @ involve check whether current log has not old edit and has new edit, if do, then return false\n
    """
    old_edits = edit_words[0]
    new_edits = edit_words[1]
    for old_edit in old_edits:
        if curr_log.find(old_edit) == -1:
            for new_edit in new_edits:
                # do not has all new, so need edit
                if curr_log.find(new_edit) == -1:
                    return True
            # has all new edit -> do not need edit
            return False

    # has all old edit -> need edit
    return True

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
    # limit the maxium none info ratio
    max_none_ratio = 0.5
    rule_size = len(rule_infos)
    max_none_size = max_none_ratio * rule_size
    none_counter = 0
    for info in rule_infos:
        if info:
            # no function or type info
            if not info.replace('_ret','').replace('_arg','') in function_info:
                return False
        else:
            # sum none counter and compare against max none size
            none_counter += 1
            if none_counter > max_none_size:
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
    # get length and transfer iterator to list
    rule_size, rule_records = my_util.get_csv_record_len(rule_records)
    repos_function_records = list(repos_function_records)
    repos_log_records = list(repos_log_records)
    # search clone instance for each rule
    for rule_record in islice(rule_records, 1, None):
        rule_counter += 1
        print 'now processing rule %d/%d, ' %(rule_counter, rule_size),
        old_loc = rule_record[my_constant.CLASS_OLD_NEW_OLD_LOC]
        check = json.loads(rule_record[my_constant.CLASS_OLD_NEW_CHECK])
        variable = json.loads(rule_record[my_constant.CLASS_OLD_NEW_VARIABLE])
        edit_words = json.loads(rule_record[my_constant.CLASS_OLD_NEW_EDIT])
        rule_feature = [check, variable]
        clone_counter_function = 0
        clone_counter_log = 0
        # insert rule -> function records
        if old_loc == '-1':
            for repos_function_record in islice(repos_function_records, 1, None):
                calls = json.loads(repos_function_record[my_constant.ANALYZE_REPOS_FUNCTION_CALLS])
                types = json.loads(repos_function_record[my_constant.ANALYZE_REPOS_FUNCTION_TYPES])
                if is_match_for_insert_rule(rule_feature, [types, calls]):
                    clone_counter_function += 1
                    necessity = check_for_insert_rule(rule_feature, \
                                repos_function_record[my_constant.ANALYZE_REPOS_FUNCTION_FUNCTION_NAME])
                    repos_function_clone_writer.writerow(rule_record + repos_function_record + [necessity])
        # modification rule -> log records
        else:
            for repos_log_record in islice(repos_log_records, 1, None):
                log_check = json.loads(repos_log_record[my_constant.CLASS_REPOS_LOG_CHECK])
                log_variable = json.loads(repos_log_record[my_constant.CLASS_REPOS_LOG_VARIABLE])
                if is_match_for_modify_rule(rule_feature, [log_check, log_variable]):
                    # get real log records from class index
                    analyze_log_records = cluster_api.generate_records_for_class(my_constant.CLUSTER_REPOS_LOG_FILE_NAME, repos_log_record[0])
                    for analyze_log_record in analyze_log_records:
                        clone_counter_log += 1
                        necessity = check_for_modify_rule(edit_words, analyze_log_record[my_constant.ANALYZE_REPOS_LOG_LOG])
                        repos_log_clone_writer.writerow(rule_record + analyze_log_record + [necessity])

        print 'find clone instances, function: %d, log: %d' %(clone_counter_function, clone_counter_log)

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