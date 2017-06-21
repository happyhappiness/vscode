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
@ involve get log location based on its location in hunk and hunk location
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
            continue
        if flag[hunk_index] < my_constant.FLAG_NO_CHANGE:
            line_delete += 1
            continue
        if flag[hunk_index] == my_constant.FLAG_NO_CHANGE:
            line_no_change += 1
            continue
    old_log_loc = old_hunk_loc + line_no_change + line_delete
    new_log_loc = new_hunk_loc + line_no_change + line_add
    return old_log_loc, new_log_loc

"""
@ param  change flag, hunk code, log update info, old hunk loc, new hunk loc and writer
@ return ...
@ callee get_loc(patch, line_count, patch_delete, change_type)
@ caller deal_patch(sha, message, changed_file, old_store_name, new_store_name, writer) ..
@ involve deal with change hunk, find modification pair
@ involve write back log modification type and old location, new location
"""
def deal_change_hunk(hunk, flag, logs, old_hunk_loc, new_hunk_loc, writer):

    len_hunk = len(hunk)
    len_log = len(logs)
    for log_index in range(len_log):
        # deal with each log to get its modification type and location
        log = logs[log_index]
        hunk_loc = log[0]
        log.pop(0)

        # -: MODIFICATION, MOVE, DELETE
        if flag[hunk_loc] == my_constant.FLAG_LOG_DELETE:

            pair_log = None
            log_type = my_constant.LOG_DELETE
            # find move pair, same hunk
            for candidate_log_index in range(log_index + 1, len_log):
                candidate_loc = logs[candidate_log_index][0]
                # add with same content
                if isinstance(candidate_loc, int) and flag[candidate_loc] == \
        my_constant.FLAG_LOG_ADD and hunk[hunk_loc].strip() == hunk[candidate_loc].strip():
                    pair_log = candidate_loc
                    log_type = my_constant.LOG_MOVE
                    break

            # MODIFY
            if pair_log is None:
                 # find MODIFICATION pair: prior to choose the pair with same delta as well as similarity
                for hunk_index in range(hunk_loc + 1, len_hunk):
                    if flag[hunk_index] == my_constant.FLAG_NO_CHANGE:
                        break
                    if flag[hunk_index] < my_constant.FLAG_NO_CHANGE:
                        continue
                    if flag[hunk_index] > my_constant.FLAG_NO_CHANGE:
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

            # MODIFICATION if find pair
            if pair_log is not None:
                log[my_constant.FETCH_LOG_CHANGE_TYPE] = log_type
                # call function to get old and new log loc by hunk loc and hunk index
                log[my_constant.FETCH_LOG_OLD_LOC], tmp =\
                     get_loc(hunk_loc, flag, old_hunk_loc, new_hunk_loc)
                tmp, log[my_constant.FETCH_LOG_NEW_LOC] =\
                     get_loc(pair_log, flag, old_hunk_loc, new_hunk_loc)
                writer.writerow(log)
                # remove pair log change
                flag[hunk_loc] = my_constant.FLAG_DELETE
                flag[pair_log] = my_constant.FLAG_ADD
            # DELETE
            else:
                log[my_constant.FETCH_LOG_CHANGE_TYPE] = my_constant.LOG_DELETE
                # call function to get old and new log loc by hunk loc and hunk index
                log[my_constant.FETCH_LOG_OLD_LOC], log[my_constant.FETCH_LOG_NEW_LOC] =\
                        get_loc(hunk_loc, flag, old_hunk_loc, new_hunk_loc)
                writer.writerow(log)
                # remove pair log change
                flag[hunk_loc] = my_constant.FLAG_DELETE
        # + : MOVE ADD
        else:
            if flag[hunk_loc] == my_constant.FLAG_LOG_ADD:
                pair_log = None
                # MOVE
                for candidate_log_index in range(log_index + 1, len_log):
                    candidate_loc = logs[candidate_log_index][0]
                    # add with same content
                    if isinstance(candidate_loc, int) and flag[candidate_loc] == \
            my_constant.FLAG_LOG_DELETE and hunk[hunk_loc].strip() == hunk[candidate_loc].strip():
                        pair_log = candidate_loc
                        log[my_constant.FETCH_LOG_CHANGE_TYPE] = my_constant.LOG_MOVE
                        # call function to get old and new log loc by hunk loc and hunk index
                        log[my_constant.FETCH_LOG_OLD_LOC], tmp =\
                            get_loc(candidate_loc, flag, old_hunk_loc, new_hunk_loc)
                        tmp, log[my_constant.FETCH_LOG_NEW_LOC] =\
                            get_loc(hunk_loc, flag, old_hunk_loc, new_hunk_loc)
                        writer.writerow(log)
                        # remove pair log change
                        flag[hunk_loc] = my_constant.FLAG_ADD
                        flag[pair_log] = my_constant.FLAG_DELETE
                        break
                # ADD
                if pair_log is None:
                    log[my_constant.FETCH_LOG_CHANGE_TYPE] = my_constant.LOG_ADD
                    # call function to get old and new log loc by hunk loc and hunk index
                    log[my_constant.FETCH_LOG_OLD_LOC], log[my_constant.FETCH_LOG_NEW_LOC] =\
                            get_loc(hunk_loc, flag, old_hunk_loc, new_hunk_loc)
                    writer.writerow(log)
                    # remove pair log change
                    flag[hunk_loc] = my_constant.FLAG_ADD

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
def deal_patch(sha, message, changed_file, old_store_name, new_store_name, writer):

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
            data_row = []
            # commit sha
            data_row.append(sha)
            # commit message
            data_row.append(message)
            # file name
            data_row.append(changed_file.filename)
            # change_type
            data_row.append(change_type)
            if change_type == '-':
                flag.append(my_constant.FLAG_LOG_DELETE)
            else:
                flag.append(my_constant.FLAG_LOG_ADD)
            # log_statement
            log_statement = is_log_change.group().strip()
            log_statement = log_statement[1:].strip()
            data_row.append(log_statement)
            # location and file info
            old_log_loc = 0
            new_log_loc = 0
            data_row.append(old_log_loc)
            data_row.append(old_store_name)
            data_row.append(new_log_loc)
            data_row.append(new_store_name)
            # hunk_loc 0->
            logs.append([hunk_loc] + data_row)
        else:
            if change_type == '-':
                flag.append(my_constant.FLAG_DELETE)
            else:
                flag.append(my_constant.FLAG_ADD)

        # update hunk location
        hunk_loc += 1

    return has_log

"""
@ param  github parameters gh and sha of commit and the counter for stored/total files and fileWriter
@ return total_log_cpp new counter of stored files, total_cpp counters of cpp files and total file all files have dealed with
@ callee deal_patch( sha, file, writer)
@ caller fetch_commit(user, repos, commit_sha='') ..
@ involve deal with commit and involved changed file
"""
def deal_commit(gh, sha, total_log_cpp, total_cpp, total_file, writer):

    # retrieve info of commit with given sha
    commit = gh.repos.commits.get(sha=sha)
    message = commit.commit.message

    # save commit patch according to files
    for changed_file in commit.files:

        # filter to just deal with cpp and c files
        is_cpp = re.search('(.cpp|.c|.cc|.cxx|.h)$', changed_file.filename, re.I)
        # filter to not deal with test module files
        is_test_cpp = re.search('(test.cpp|test.c)$', changed_file.filename, re.I)
        # do not deal with removed files
        is_removed = changed_file.status
        if is_cpp and not is_test_cpp and is_removed != 'removed':
            # increment the total file count
            total_cpp = total_cpp + 1

            # define old/new_store_name
            base_store_name = '/data/download/' + my_constant.REPOS + '/' + my_constant.REPOS \
                + '/' + my_constant.USER + '_' + my_constant.REPOS + '_' + str(total_log_cpp)
            new_store_name = base_store_name + '_new.cpp'
            old_store_name = base_store_name + '_old.cpp'

            # call deal_patch to deal with the patch file
            has_log = deal_patch(sha, message, changed_file, old_store_name, new_store_name, writer)
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
        # invoke the deal_commit function
        total_log_cpp, total_cpp, total_file = deal_commit \
                            (gh, commit.sha, total_log_cpp, total_cpp, total_file, hunk_writer)
        if total_file % 10 == 0:
            print 'now have deal with %d none cpp file ; find cpp %d file ; have saved %d file ' %(total_file, total_cpp, total_log_cpp)
    # deal_commit(gh, commit_sha, writer)

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
    # deal with hunk