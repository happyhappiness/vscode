#-*-coding: utf-8 -*-
import os
import csv
import json
from itertools import islice
import my_util
import my_constant
import cluster_api
import analyze_control_repos

def check_given_log_in_function(function_name, check, variable, postfix=''):
    """
    @ param function name, check and variable constaints and postfix\n
    @ return true if has that kind of log\n
    @ involve traverse log analysis data and try to find logs statisfying given constraints\n
    """
    log_file = file(my_util.concate_file(\
            my_constant.ANALYZE_REPOS_LOG_FILE_NAME, postfix), 'rb')
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

def check_for_insert_rule(rule_feature, function, postfix=''):
    """
    @ param rule feature(check, variable) and function name and postfix\n
    @ return true if need insert log\n
    @ involve check whether there is log that do given check and output given variable, if do, return false\n
    """
    check = rule_feature[0]
    variable = rule_feature[1]
    # has log -> no need
    if check_given_log_in_function(function, check, variable, postfix):
        return "accept-false"
    else:
        return "accept-true"

def check_for_modify_rule(edit_words, curr_log):
    """
    @ param edit words(old edits and new edits)\n
    @ return true if need edit\n
    @ involve check whether current log has not old edit and has new edit, if do, then return false\n
    """
    old_edits = edit_words[0]
    new_edits = edit_words[1]
    # just add new things
    # if old_edits == []:
    #     for new_edit in new_edits:
    #         # do not has all new
    #         if curr_log.find(new_edit) == -1:
    #             return "accept-true"
    #         # has all new edit -> do not need edit
    #         return "accept-false"
    # update old, so check whether old exist
    for old_edit in old_edits:
        if curr_log.find(old_edit) == -1:
            # for deleted log, must be same old log
            if new_edits == []:
                return "reject"
            for new_edit in new_edits:
                # do not has all new, and do not has all old
                if curr_log.find(new_edit) == -1:
                    return "reject"
            # has all new edit -> do not need edit
            return "accept-false"

    # has all old edit -> need edit
    return "accept-true"

def filter_insert_rule(rule_feature, none_ratio=0.5):
    """
    @ param rule feature, maximum none ratio of insert rule feature\n
    @ return true if pass filter\n
    @ involve check insert rule feature must not has more none feature than maximum none ratio\n
    """
    rule_feature = rule_feature[0] + rule_feature[1]
    if rule_feature.count(None) > len(rule_feature) * none_ratio:
        return False
    else:
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
    for info in rule_infos:
        if info and not info.replace('_ret','').replace('_arg','') in function_info:
            return False
    return True

def is_match_for_modify_rule(rule_feature, repos_log_feature):
    """
    @ param rule feature(check, variable) and repos log feature(check, variable)\n
    @ return true if match\n
    @ involve validate that check and variable info must be exactly same\n
    """
    return rule_feature == repos_log_feature

def check_repos_info(repos_name, repos_list=[], rebuild_repos=False, postfix=''):
    """
    @ param repos name and repos list of analyzed repos and flag: true if srcml api update), file postfix\n
    @ return nothing\n
    @ involve create repos info for given old repos name if need\n
    """
    # has file
    if os.path.isfile(my_util.concate_file(my_constant.ANALYZE_REPOS_LOG_FILE_NAME, \
                    postfix)):
        # need rebuild, then check dict(in dict -> nothing)
        if rebuild_repos:
            if repos_name in repos_list:
                return repos_list
        # do not need rebuild -> nothing
        else:
            return repos_list
    # has no file or has file and no key -> re analyze repos
    # analyze repos of given repos name and postfix
    analyze_control_repos.analyze_repos(repos_name, postfix=postfix)
    # only cluster log for fix repos
    if postfix == my_constant.LAST_REPOS or postfix == '':
        analyze_control_repos.cluster_repos_log(postfix)
    # add to dict
    repos_list.append(repos_name)
    return repos_list

def seek_clone(repos_name, rebuild_repos=False, postfix=''):
    """
    @ param postfix: repos info files \n
    @ return nothing \n
    @ involve match rule class against given repos log class and function\n
    """
    # check repos according to rebuild repos flag(warn:no repos list)
    check_repos_info(repos_name, [], rebuild_repos, postfix)
    # initiate csv reader file(rule class, repos log class, function class)
    rule_file = file(my_constant.CLASS_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME, 'rb')
    rule_records = csv.reader(rule_file)
    repos_log_class_file = file(my_util.concate_file(\
                my_constant.CLASS_REPOS_LOG_FILE_NAME, postfix), 'rb')
    repos_log_records = csv.reader(repos_log_class_file)
    repos_function_file = file(my_util.concate_file(\
                my_constant.ANALYZE_REPOS_FUNCTION_FILE_NAME, postfix), 'rb')
    repos_function_records = csv.reader(repos_function_file)
    # initiate csv writer file(repos log clone and function clone)
    repos_log_clone_file = file(my_util.concate_file(\
                my_constant.ANALYZE_CLONE_LOG_FILE_NAME, postfix), 'wb')
    repos_log_clone_writer = csv.writer(repos_log_clone_file)
    repos_log_clone_writer.writerow(my_constant.ANALYZE_CLONE_LOG_TITLE)
    repos_function_clone_file = file(my_util.concate_file(\
                my_constant.ANALYZE_CLONE_FUNCTION_FILE_NAME, postfix), 'wb')
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
                repos_function_record[my_constant.ANALYZE_REPOS_FUNCTION_FUNCTION_NAME], postfix)
                    repos_function_clone_writer.writerow(rule_record + \
                                              repos_function_record + [necessity])
        # modification rule -> log records
        else:
            for repos_log_record in islice(repos_log_records, 1, None):
                log_check = json.loads(repos_log_record[my_constant.CLASS_REPOS_LOG_CHECK])
                log_variable = json.loads(repos_log_record[my_constant.CLASS_REPOS_LOG_VARIABLE])
                if is_match_for_modify_rule(rule_feature, [log_check, log_variable]):
                    # get real log records from class index
                    analyze_log_records = cluster_api.generate_records_for_class(my_util.concate_file(\
                            my_constant.CLUSTER_REPOS_LOG_FILE_NAME, postfix), repos_log_record[0])
                    for analyze_log_record in analyze_log_records:
                        clone_counter_log += 1
                        necessity = check_for_modify_rule(edit_words, \
                                analyze_log_record[my_constant.ANALYZE_REPOS_LOG_LOG])
                        repos_log_clone_writer.writerow(rule_record + \
                                            analyze_log_record[:-1] + [necessity])

        print 'find clone instances, function: %d, log: %d' \
                         %(clone_counter_function, clone_counter_log)

    # close file
    rule_file.close()
    repos_log_class_file.close()
    repos_function_file.close()
    repos_function_clone_file.close()
    repos_log_clone_file.close()

def seek_clone_for_corresponding_repos(rebuild_repos=False):
    """
    @ param true if need reanalyze repos database(e.g. srcml_api update)\n
    @ return nothing \n
    @ involve match each rule with their corresponding repos(log and function)\n
    """
    # initiate csv reader file(rule class, repos log class, function class)
    rule_file = file(my_constant.CLASS_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME, 'rb')
    rule_records = csv.reader(rule_file)
    # initiate csv writer file(repos log clone and function clone)
    repos_log_clone_file = file(my_util.concate_file(\
                my_constant.ANALYZE_CLONE_LOG_FILE_NAME, '_rule'), 'wb')
    repos_log_clone_writer = csv.writer(repos_log_clone_file)
    repos_log_clone_writer.writerow(my_constant.ANALYZE_CLONE_LOG_TITLE)
    repos_function_clone_file = file(my_util.concate_file(\
                    my_constant.ANALYZE_CLONE_FUNCTION_FILE_NAME, '_rule'), 'wb')
    repos_function_clone_writer = csv.writer(repos_function_clone_file)
    repos_function_clone_writer.writerow(my_constant.ANALYZE_CLONE_FUNCTION_TITLE)
    rule_counter = 0
    # get length and transfer iterator to list
    rule_size, rule_records = my_util.get_csv_record_len(rule_records)
    # list of analyzed reposes
    repos_list = []
    # search clone instance for each rule
    for rule_record in islice(rule_records, 1, None):
        rule_counter += 1
        print 'now processing rule %d/%d, ' %(rule_counter, rule_size)
        # get cluster record from rule class, since one rule may correspond to multi reposes
        rule_cluster_records = cluster_api.generate_records_for_class(\
                my_constant.CLUSTER_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME, rule_record[0])
        # rule info
        old_loc = rule_record[my_constant.CLASS_OLD_NEW_OLD_LOC]
        check = json.loads(rule_record[my_constant.CLASS_OLD_NEW_CHECK])
        variable = json.loads(rule_record[my_constant.CLASS_OLD_NEW_VARIABLE])
        edit_words = json.loads(rule_record[my_constant.CLASS_OLD_NEW_EDIT])
        rule_feature = [check, variable]
        # deal with each repos for this rule
        rule_repos_list = []
        for rule_cluster_record in rule_cluster_records:
            # get repos info files with old repos name
            old_repos_name = my_util.get_old_repos_name(rule_cluster_record[0])
            postfix = '_' + old_repos_name
            repos_list = check_repos_info(old_repos_name, repos_list, rebuild_repos, postfix)
            # do not reanalyze rule
            if old_repos_name in rule_repos_list:
                continue
            rule_repos_list.append(old_repos_name)
            # clone counter
            clone_counter_function = 0
            clone_counter_log = 0
            # insert rule -> function records
            if old_loc == '-1':
                # filter insert rule with information ratio
                if not filter_insert_rule(rule_feature):
                    continue
                repos_function_file = file(my_util.concate_file(\
                        my_constant.ANALYZE_REPOS_FUNCTION_FILE_NAME, postfix))
                repos_function_records = csv.reader(repos_function_file)
                for repos_function_record in islice(repos_function_records, 1, None):
                    calls = json.loads(repos_function_record[my_constant.ANALYZE_REPOS_FUNCTION_CALLS])
                    types = json.loads(repos_function_record[my_constant.ANALYZE_REPOS_FUNCTION_TYPES])
                    # match rule info against function info
                    if is_match_for_insert_rule(rule_feature, [types, calls]):
                        clone_counter_function += 1
                        necessity = check_for_insert_rule(rule_feature, \
                    repos_function_record[my_constant.ANALYZE_REPOS_FUNCTION_FUNCTION_NAME], postfix)
                        repos_function_clone_writer.writerow(rule_record + repos_function_record + [necessity])
                # close file
                repos_function_file.close()
            # modification rule -> log records
            else:
                repos_log_file = file(my_util.concate_file(\
                            my_constant.ANALYZE_REPOS_LOG_FILE_NAME, postfix))
                repos_log_records = csv.reader(repos_log_file)
                for repos_log_record in islice(repos_log_records, 1, None):
                    log_check = json.loads(repos_log_record[my_constant.ANALYZE_REPOS_LOG_CHECK])
                    log_variable = json.loads(repos_log_record[my_constant.ANALYZE_REPOS_LOG_VARIABLE])
                    # match rule info against log info
                    if is_match_for_modify_rule(rule_feature, [log_check, log_variable]):
                        clone_counter_log += 1
                        necessity = check_for_modify_rule(edit_words, \
                                repos_log_record[my_constant.ANALYZE_REPOS_LOG_LOG])
                        repos_log_clone_writer.writerow(rule_record + repos_log_record + [necessity])

                # close repos info files
                repos_log_file.close()
        print 'find clone instances, function: %d, log: %d' \
                        %(clone_counter_function, clone_counter_log)

    # close file
    repos_function_file.close()
    repos_function_clone_file.close()
    repos_log_clone_file.close()

def seek_clone_for_lastest_repos(rebuild_repos=False):
    """
    @ param flag: true if need rebuild repos info\n
    @ return nothing\n
    @ involve match every rule against latest repos\n
    """
    seek_clone(my_constant.LAST_REPOS, rebuild_repos, my_constant.LAST_REPOS)

"""
main function
"""
if __name__ == "__main__":

    seek_clone_for_corresponding_repos(True)
    # list_a = [[["!", "struct group_of_users *"]], [["strstr", "char *", "\"group \"", "char *", "=="]]]
    # list_b = [[["!", "struct user *"]], [["strstr", "char *", "\"user \"", "char *", "=="]]]
    # print compute_context_similarity(list_a, list_b, {})