#-*-coding: utf-8 -*-
from pygithub3 import Github
import csv
import sys
import re
import commands
import base64
import my_constant
import json
import myUtil
from itertools import islice

reload(sys);
sys.setdefaultencoding('utf8')

"""
@ param hunk location, flag info and log location in hunk
@ return log_loc
@ callee ..
@ caller deal_change_hunk(flag, hunk, logs, old_hunk_loc, new_hunk_loc, writer)
@ involve get log location based on its location in hunk and hunk edit flag
"""
def get_loc(hunk_loc, flag, old_hunk_loc, new_hunk_loc):

    line_delete = 0
    line_add = 0
    line_no_change = 0
    old_log_loc = 0
    new_log_loc = 0
    for hunk_index in range(0, hunk_loc):
        if flag[hunk_index] > my_constant.FLAG_NO_CHANGE:
            line_add += 1
        elif flag[hunk_index] < my_constant.FLAG_NO_CHANGE:
            line_delete += 1
        elif flag[hunk_index] == my_constant.FLAG_NO_CHANGE:
            line_no_change += 1
    # just like count lines
    old_log_loc = old_hunk_loc + line_no_change + line_delete
    new_log_loc = new_hunk_loc + line_no_change + line_add
    return old_log_loc, new_log_loc

"""
@ param  change flag, hunk code, logs in hunk, index in logs, and hunk location of specific log
@ return log_type, pair_log
@ callee nothing
@ caller deal_change_hunk(hunk, flag, logs, old_hunk_loc, new_hunk_loc, writer) ..
@ involve make sure change type for specific log [move > modify > add/delete]
"""
def find_log_change_type(hunk, flag, logs, log_index, hunk_loc):
    # edit type and log/hunk length
    edit_type = flag[hunk_loc]
    if edit_type == my_constant.FLAG_DELETE or edit_type == my_constant.FLAG_ADD:
        return None, edit_type, None
    pair_edit_type = -1 * edit_type
    len_log = len(logs)
    len_hunk = len(hunk)

    log_type = None
    pair_log = None
    # MOVE [same hunk info]
    for candidate_log_index in range(log_index + 1, len_log):
        candidate_loc = logs[candidate_log_index][0]
        # add with same content while opposite edit type
        if isinstance(candidate_loc, int) and flag[candidate_loc] == pair_edit_type \
        and get_log_statement(flag, hunk, hunk_loc) == get_log_statement(flag, hunk, candidate_loc):
            pair_log = candidate_loc
            log_type = my_constant.LOG_MOVE
            return log_type, edit_type, pair_log

    # MODIFY FOR DELETE[prior to choose the pair with same delta as well as similarity]
    if edit_type == my_constant.FLAG_LOG_DELETE:
        log_type = my_constant.LOG_DELETE
        for hunk_index in range(hunk_loc + 1, len_hunk):
            if flag[hunk_index] == my_constant.FLAG_NO_CHANGE:
                break
            elif flag[hunk_index] > my_constant.FLAG_NO_CHANGE:
                # backtrace to find - start location
                delta = 0
                backward_index = hunk_loc - 1
                while backward_index >= 0:
                    if flag[backward_index] < my_constant.FLAG_NO_CHANGE:
                        delta += 1
                        backward_index -= 1
                    else:
                        break
                # compute corresponding pair location
                forward_index = min(delta + hunk_index, len_hunk - 1)
                if flag[forward_index] == my_constant.FLAG_LOG_ADD:
                    pair_log = forward_index
                    log_type = my_constant.LOG_MODIFY
                else:
                    # traverse neighbors
                    for neighbor_index in range(max(0, forward_index - 5), min(forward_index + 5, len_hunk)):
                        if flag[neighbor_index] == my_constant.FLAG_LOG_ADD:
                            pair_log = neighbor_index
                            log_type = my_constant.LOG_MODIFY
                break
        # no add break or after dealing break
        return log_type, edit_type, pair_log

    # log add with no pairs
    return my_constant.LOG_ADD, edit_type, pair_log
"""
@ param two edit statements
@ return modification
@ callee myUtil
@ caller deal_change_hunk(hunk, flag, logs, old_hunk_loc, new_hunk_loc, writer) ..
@ involve get modification set from two edit statements(conconated)
"""
def get_modification(edit_statements_one, edit_statements_two = ''):
    edit_set_one = set(re.split(my_constant.SPLIT_STR, edit_statements_one.lower()))
    edit_set_two = set(re.split(my_constant.SPLIT_STR, edit_statements_two.lower()))
    modification = myUtil.get_delta_of_two_set(edit_set_one, edit_set_two)
    return modification


"""
@ param old flag info, hunk statements and logs
@ return new flag info
@ callee nothing
@ caller deal_change_hunk(hunk, flag, logs, old_hunk_loc, new_hunk_loc)
@ involve mark log continue flag util encounter ; or differenr marked flag
"""
def flag_log_continue(flag, hunk, logs):
    len_hunk = len(hunk)
    for log in logs:
        hunk_loc = log[0]
        edit_type = flag[hunk_loc]
        # encounter with ; at the log location
        if hunk[hunk_loc].find(';') != -1:
            continue
        for hunk_index in range(hunk_loc + 1, len_hunk):
            # no different flag and no encounter ;
            if flag[hunk_index] * edit_type > 0:
                flag[hunk_index] = edit_type / my_constant.FLAG_LOG_ADD * \
                                    my_constant.FLAG_LOG_ADD_CONTINUE
                # encounter the end ;
                if hunk[hunk_index].find(';') != -1:
                    break
            # encounter different marked flag
            else:
                break

    return flag

"""
@ param flag nfo and hunk statements
@ return feature modified set
@ callee get_modification(edit_statements_one, edit_statements_two = '')
@ caller deal_change_hunk(hunk, flag, logs, old_hunk_loc, new_hunk_loc)
@ involve get modified statements set
"""
def get_feature_modify_set(flag, hunk):
    # compute modification set (lose frequency modification)
    add = ''
    delete = ''
    len_hunk = len(hunk)
    for hunk_index in range(len_hunk):
        if flag[hunk_index] == my_constant.FLAG_DELETE:
            delete += hunk[hunk_index].strip() + '\n'
        elif flag[hunk_index] == my_constant.FLAG_ADD:
            add += hunk[hunk_index].strip() + '\n'
    feature_modified_set = get_modification(add, delete)

    return feature_modified_set

"""
@ param flag info, hunk statements and location of log
@ return log statements
@ callee nothing
@ caller get_log_modify_set, find_log_change_type
@ involve get log statement with consideration of log continue
"""
def get_log_statement(flag, hunk, hunk_loc):
    hunk_statement = hunk[hunk_loc].strip() + '\n'
    len_hunk = len(hunk)
    for hunk_index in range(hunk_loc + 1, len_hunk):
        if abs(flag[hunk_index]) == my_constant.FLAG_LOG_ADD_CONTINUE:
            hunk_statement += hunk[hunk_index].strip() + '\n'
        else:
            break
    return hunk_statement

"""
@ param flag info, hunk statements and location of log and its paired log
@ return log modified set
@ callee get_modification(edit_statements_one, edit_statements_two = ''), get_log_statement
@ caller deal_change_hunk(hunk, flag, logs, old_hunk_loc, new_hunk_loc)
@ involve get modified statements set of given log
"""
def get_log_modify_set(flag, hunk, hunk_loc, pair_log):
    hunk_statement = get_log_statement(flag, hunk, hunk_loc)
    pair_statement = ''
    # try to filter the co change log
    if pair_log is not None:
        pair_statement = get_log_statement(flag, hunk, pair_log)
    log_modified_set = get_modification(hunk_statement, pair_statement)
    return log_modified_set

"""
@ param  change flag, hunk code, log update info, old hunk loc, new hunk loc and writer
@ return ...
@ callee get_loc, is_dependent_log_change, myUtil, find_log_change_type ...
@ caller deal_patch(sha, message, changed_file, old_store_name, new_store_name, writer) ..
@ involve deal with change hunk, find modification pair
@ involve write back log modification type and old location, new location
"""
def deal_change_hunk(hunk, flag, logs, old_hunk_loc, new_hunk_loc, writer):

    # flag log continue
    flag = flag_log_continue(flag, hunk, logs)
    # get modified set
    feature_modified_set = get_feature_modify_set(flag, hunk)

    len_log = len(logs)
    for log_index in range(len_log):
        # deal with each log to get its modification type and location
        log = logs[log_index]
        hunk_loc = log[0]
        # try find log type and pair log
        log_type, edit_type, pair_log = find_log_change_type(hunk, flag, logs, log_index, hunk_loc)
        if log_type is None:
            continue

        # get log modified set
        log_modified_set = get_log_modify_set(flag, hunk, hunk_loc, pair_log)
        if feature_modified_set.issuperset(log_modified_set):
            log_type = my_constant.LOG_COCHANGE

        # modify log type and location info
        log.pop(0)
        log[my_constant.FETCH_LOG_CHANGE_TYPE] = log_type
        # modify log location info according to log_type(pair_log is none or not)
        if pair_log is not None:
            # for log delete -> old_loc(hunk_loc), new_loc(pair_log)
            if edit_type < my_constant.FLAG_NO_CHANGE:
                for_old_loc = hunk_loc
                for_new_loc = pair_log
            # for log add -> old_loc(pair_log), new_loc(hunk_loc)
            else:
                for_old_loc = pair_log
                for_new_loc = hunk_loc
            log[my_constant.FETCH_LOG_OLD_LOC], tmp = \
                     get_loc(for_old_loc, flag, old_hunk_loc, new_hunk_loc)
            tmp, log[my_constant.FETCH_LOG_NEW_LOC] =\
                    get_loc(for_new_loc, flag, old_hunk_loc, new_hunk_loc)
            # mark have dealed with paired log
            flag[pair_log] = -1 * edit_type / 2
        else:
            log[my_constant.FETCH_LOG_OLD_LOC], log[my_constant.FETCH_LOG_NEW_LOC] =\
                        get_loc(hunk_loc, flag, old_hunk_loc, new_hunk_loc)
        # mark have dealed with specific log
        flag[hunk_loc] = edit_type / 2
        writer.writerow(log)

"""
@ param flag about wheter to read hunk from file
@ return ...
@ callee deal_change_hunk(hunk, flag, logs, old_hunk_loc, new_hunk_loc)
@ caller 
@ involve initialize hunk file reader and log file writer, deal with each hunk
"""
def fetch_hunk(is_from_file, commit_sha):

    # initialize writer
    log_file = file(my_constant.FETCH_LOG_FILE_NAME, 'wb')
    # log_file = file('data/fetch/tmp-out.csv', 'wb')
    log_writer = csv.writer(log_file)
    log_writer.writerow(my_constant.FETCH_LOG_TITLE)
    if not is_from_file:
        fetch_commit(commit_sha)
    # initialize reader
    hunk_reader = file(my_constant.FETCH_HUNK_FILE_NAME, 'rb')
    # hunk_reader = file('data/fetch/tmp.csv', 'rb')
    hunk_records = csv.reader(hunk_reader)
    hunk_count = 0
    for hunk_record in islice(hunk_records, 1, None):
        hunk = json.loads(hunk_record[my_constant.FETCH_HUNK_HUNK])
        flag = json.loads(hunk_record[my_constant.FETCH_HUNK_FLAG])
        logs = json.loads(hunk_record[my_constant.FETCH_HUNK_LOGS])
        old_hunk_loc = int(hunk_record[my_constant.FETCH_HUNK_OLD_HUNK_LOC])
        new_hunk_loc = int(hunk_record[my_constant.FETCH_HUNK_NEW_HUNK_LOC])
        deal_change_hunk(hunk, flag, logs, old_hunk_loc, new_hunk_loc, log_writer)
        print 'now dealing with no. %d hunk' %hunk_count
        hunk_count += 1
    log_file.close()
    hunk_reader.close()

"""
@ param  commit sha sha, changed cpp file file, stored file name new/old_store_name, csv writer writer
@ return bool has log (whether this patch contained log or not)
@ callee ...
@ caller  deal_commit(gh, sha, writer) ..
@ involve deal with patch file and save hunk info(with log)
"""
def deal_patch(commit_info, changed_file, old_store_name, new_store_name, writer):

    has_log = False

    # try exception to validate patch existence
    try:
        # divide mutiline string into single lines
        patch = changed_file.patch.split('\n')
    except AttributeError as ae:
        print ae.message
        return has_log

    # flag to record change type(0/1/2)
    flag = []
    # hunk patch content
    hunk = []
    # log change in hunk
    logs = []
    # old file location and new file location of hunk top
    old_hunk_loc = 0
    new_hunk_loc = 0
    hunk_loc = 0
    # filter out the one with log statement changes
    log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)
    log_function = myUtil.functionToRegrexStr(log_functions)
    pattern_log = '^(-|\+)([^/]*(?:'+ log_function + ')[\w]*[\d]*)\((.*)$'

    # deal with each line of patch
    for line in patch:
        # recognize change hunk by description info
        is_hunk = re.match('^@@.*-(.*),.*\+(.*),.*@@', line)
        # deal with past hunk and record new one
        if is_hunk:
            # if has log update, so deal with it
            if not len(logs) == 0:
                has_log = True
                # deal_change_hunk(hunk, flag, logs, old_hunk_loc, new_hunk_loc, writer)
                hunk = json.dumps(hunk)
                flag = json.dumps(flag)
                logs = json.dumps(logs)
                writer.writerow([hunk, flag, logs, old_hunk_loc, new_hunk_loc])
            old_hunk_loc = is_hunk.group(1)
            new_hunk_loc = is_hunk.group(2)
            hunk_loc = 0
            flag = []
            hunk = []
            logs = []
            continue

        # record hunk content
        hunk.append(line[1:])

        # record change type flag
        change_type = line[0]
        if not change_type == '-':
            if not change_type == '+':
                flag.append(my_constant.FLAG_NO_CHANGE)
                # update hunk location
                hunk_loc += 1
                continue

        # record log info
        # decide if it belongs to log change
        is_log_change = re.match(pattern_log, line, re.I)
        if is_log_change:
            # store this changed log statement
            commit_info.append(changed_file.filename)
            # change_type
            commit_info.append(change_type)
            if change_type == '-':
                flag.append(my_constant.FLAG_LOG_DELETE)
            else:
                flag.append(my_constant.FLAG_LOG_ADD)
            # log_statement
            log_statement = is_log_change.group().strip()
            log_statement = log_statement[1:].strip()
            commit_info.append(log_statement)
            # location and file info
            old_log_loc = 0
            new_log_loc = 0
            commit_info.append(old_log_loc)
            commit_info.append(old_store_name)
            commit_info.append(new_log_loc)
            commit_info.append(new_store_name)
            # hunk_loc 0->
            logs.append([hunk_loc] + commit_info)
        else:
            if change_type == '-':
                flag.append(my_constant.FLAG_DELETE)
            else:
                flag.append(my_constant.FLAG_ADD)

        # update hunk location
        hunk_loc += 1

    return has_log


"""
@ param gh and sha
@ return commit, message
@ callee nothing
@ caller deal commit...
@ involve filter out commit which has dealed before (sha, file number, file name)
"""
def filter_commit(gh, sha):

    # commit info
    commit = gh.repos.commits.get(sha=sha)
    message = commit.commit.message

    # has brother
    is_has_brother = re.search(r'\n([0-9a-fA-F]{6,8})\s', message, re.M)
    # do not deal with top ones
    if is_has_brother:
        return None, None
    else:
        # deal to get issue number
        issue_numbers = re.findall(r'#(\d{1,5})', message, re.M)
        issue_addresses = []
        for issue_number in issue_numbers:
            issue_addresses.append(my_constant.ISSUE_ADDRESS + issue_number)
        commit_info = [sha, message, issue_addresses]

        return commit, commit_info

"""
@ param gh and sha
@ return commit, message
@ callee nothing
@ caller deal commit...
@ involve filter out file which is not cpp like
@ involve or not modified
"""
def filter_file(changed_file):

    # cpp like
    is_cpp = re.search(r'(.cpp|.c|.cc|.cxx|.h)$', changed_file.filename, re.I)
    # test like
    # is_test_cpp = re.search(r'(test)$', changed_file.filename, re.I)
    # modified
    is_removed = changed_file.status
    if is_cpp and is_removed == 'modified':
        return True
    else:
        return False

"""
@ param  github parameters gh and sha of commit and the counter for stored/total files and fileWriter
@ return total_log_cpp new counter of stored files, total_cpp counters of cpp files and total file all files have dealed with
@ callee deal_patch( sha, file, writer)
@ caller fetch_commit(user, repos, commit_sha='') ..
@ involve deal with commit and involved changed file
"""
def deal_commit(gh, sha, total_log_cpp, total_cpp, total_file, writer):

    # filter sha by message and retrieve info if pass
    commit, commit_info = filter_commit(gh, sha)
    if commit is not None:

        # deal with changed file and save patch with log modifications
        for changed_file in commit.files:

            # filter file to choose the modified cpp like file
            is_ok = filter_file(changed_file)
            if is_ok:
                # increment the total file count
                total_cpp = total_cpp + 1

                # old/new_store_name
                base_store_name = '/data/download/' + my_constant.REPOS + '/' + my_constant.REPOS \
                    + '/' + my_constant.USER + '_' + my_constant.REPOS + '_' + str(total_log_cpp)
                new_store_name = base_store_name + '_new.cpp'
                old_store_name = base_store_name + '_old.cpp'

                # call deal_patch to deal with the patch file
                has_log = deal_patch(commit_info, changed_file, old_store_name, new_store_name, writer)
                if has_log:
                    # download the blob of file
                    source = gh.git_data.blobs.get(changed_file.sha).content
                    # decode to retrieve the source file
                    source = base64.b64decode(source)

                    # write new file to temp file
                    temp_file = open(new_store_name, 'wb')
                    temp_file.write(source)
                    temp_file.close()

                    # write patch file to temp file
                    patch_store_name = '/data/download/temp.cpp'
                    temp_file = open(patch_store_name, 'wb')
                    temp_file.write(changed_file.patch)
                    temp_file.close()

                    # get old file with patch cmd and write back
                    output = commands.getoutput('patch -R ' + new_store_name \
                            + ' -i ' + patch_store_name + ' -o ' + old_store_name)
                    output = commands.getoutput('rm ' + patch_store_name)

                    # increment the file count
                    total_log_cpp += 1
            else:
                total_file += 1

    return total_log_cpp, total_cpp, total_file


"""
@ param  configuration parameters like user, repos and start_sha
@ return nothing 
@ callee deal_commit(gh, sha, writer)
@ caller fetch_hunk
@ involve fetch and analyze each commit and save hunk info with log
"""
def fetch_commit(commit_sha=''):

    # initiate Github with given user and repos
    gh = Github(login='993273596@qq.com', password='nx153156', user=my_constant.USER, repo=my_constant.REPOS)

    # initiate csvfile which store the commit info
    hunk_file = file(my_constant.FETCH_HUNK_FILE_NAME, 'wb')
    hunk_writer = csv.writer(hunk_file)
    hunk_writer.writerow(my_constant.FETCH_HUNK_TITLE)

    # fetch all the commits of given repos
    commits = gh.repos.commits.list(sha=commit_sha)
    total_file = 0
    total_cpp = 0
    total_log_cpp = 0
    for commit in commits.iterator():
        # call deal_commit function to deal with each commit
        total_log_cpp, total_cpp, total_file = deal_commit \
                            (gh, commit.sha, total_log_cpp, total_cpp, total_file, hunk_writer)
        if total_file % 10 == 0:
            print 'now have deal with %d none cpp file ; find cpp %d file ; \
                        have saved %d file ' %(total_file, total_cpp, total_log_cpp)

    # close the commit file
    hunk_file.close()

"""
main function
"""
if __name__ == "__main__":
    # several configuration constant: user, repos
    # user = 'mongodb'
    # repos = 'mongo'
    # user = 'torvalds'
    # repos = 'linux'

    commit_sha = ''
    # with function to retieve all the commits of given path
    fetch_hunk(True, commit_sha)
    # filter_commit(gh, commit_sha)
    # deal with hunk
