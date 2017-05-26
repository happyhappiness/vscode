#-*-coding: utf-8 -*-
from pygithub3 import Github
import csv
import sys
import re
import commands
import base64
import myUtil
import analyze_control_clone

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
        if flag[hunk_index] == myUtil.FLAG_ADD:
            line_add += 1
            continue
        if flag[hunk_index] == myUtil.FLAG_DELETE:
            line_delete += 1
            continue
        if flag[hunk_index] == myUtil.FLAG_NO_CHANGE:
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
def deal_change_hunk(flag, hunk, logs, old_hunk_loc, new_hunk_loc, writer):

    len_hunk = len(hunk)
    len_log = len(logs)
    for log_index in range(len_log):
        # deal with each log to get its modification type and location
        log = logs[log_index]
        hunk_loc = log[0]
        log.pop(0)
        # already paired
        if flag[hunk_loc] == myUtil.FLAG_NO_CHANGE:
            continue
        # get change type and log statement
        change_type = log[myUtil.FETCH_CHANGE_TYPE]
        log_statement = log[myUtil.FETCH_LOG]
        # try to fing pair for modification
        if flag[hunk_loc] == myUtil.FLAG_DELETE:
            # backtrace to find - start location
            delta = 0
            hunk_index = hunk_loc - 1
            while hunk_index >= 0:
                if flag[hunk_index] == myUtil.FLAG_DELETE:
                    delta += 1
                else:
                    break
            # forward going to find pair for delete
            add_delta = 0
            pair_log = None
            # prior to choose the pair with same delta
            max_score = -1
            for hunk_index in range(hunk_loc, len_hunk):
                if flag[hunk_index] == myUtil.FLAG_DELETE:
                    continue
                if flag[hunk_index] == myUtil.FLAG_NO_CHANGE:
                    break
                if flag[hunk_index] == myUtil.FLAG_ADD:
                    hunk_score = float(abs(delta - add_delta))*len(log_statement)/2
                    curr_score = myUtil.longestCommon(log, logs[hunk_index]) - hunk_score
                    if curr_score > max_score:
                        max_score = curr_score
                        pair_log = hunk_index
                    add_delta += 1

            # MODIFICATION if find pair
            if pair_log is not None:
                log[myUtil.FETCH_CHANGE_TYPE] = myUtil.LOG_MODIFY
                # call function to get old and new log loc by hunk loc and hunk index
                log[myUtil.FETCH_OLD_LOC], log[myUtil.FETCH_NEW_LOC] =\
                     get_loc(hunk_loc, flag, old_hunk_loc, new_hunk_loc)
                writer.writerow(log)
                # remove pair log change
                flag[hunk_loc] = myUtil.FLAG_NO_CHANGE
                flag[pair_log] = myUtil.FLAG_NO_CHANGE
                continue

            # DELETE
            log[myUtil.FETCH_CHANGE_TYPE] = myUtil.LOG_DELETE
            # call function to get old and new log loc by hunk loc and hunk index
            log[myUtil.FETCH_OLD_LOC], log[myUtil.FETCH_NEW_LOC] =\
                    get_loc(hunk_loc, flag, old_hunk_loc, new_hunk_loc)
            writer.writerow(log)
            # remove pair log change
            flag[hunk_loc] = myUtil.FLAG_NO_CHANGE
            continue
        # ADD
        log[myUtil.FETCH_CHANGE_TYPE] = myUtil.LOG_ADD
        # call function to get old and new log loc by hunk loc and hunk index
        log[myUtil.FETCH_OLD_LOC], log[myUtil.FETCH_NEW_LOC] =\
                get_loc(hunk_loc, flag, old_hunk_loc, new_hunk_loc)
        writer.writerow(log)
        # remove pair log change
        flag[hunk_loc] = myUtil.FLAG_NO_CHANGE

"""
@ param  commit sha sha, changed cpp file file, stored file name new/old_store_name, csv writer writer
@ return bool has log (whether this patch contained log or not)
@ callee get_loc(patch, line_count, patch_delete, change_type)
@ caller  deal_commit(gh, sha, writer) ..
@ involve deal with patch file and save commit info (just store and analyze +)
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
    log_functions = myUtil.retrieveLogFunction(myUtil.LOG_CALL_FILE_NAME)
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
                deal_change_hunk(flag, hunk, logs, old_hunk_loc, new_hunk_loc, writer)
            old_hunk_loc = int(is_hunk.group(1))
            new_hunk_loc = int(is_hunk.group(2))
            hunk_loc = 0
            flag = []
            hunk = []
            logs= []
            continue
        
        # record change type flag
        change_type = line[0]
        if change_type == '-':
            flag.append(myUtil.FLAG_DELETE)
        else:
            if change_type == '+':
                flag.append(myUtil.FLAG_ADD)
            else:
                # no change so no log change: increment line_count and continue
                flag.append(myUtil.FLAG_NO_CHANGE)
                continue

        
        # record hunk content
        hunk.append(line.pop(0))

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
            logs.append(hunk_loc + datarow)
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
            base_store_name = '/data/download/' + myUtil.REPOS + '/' + myUtil.REPOS \
                + '/' + myUtil.USER + '_' + myUtil.REPOS + '_' + str(total_log_cpp)
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
@ caller main ..
@ involve save commit info of given repos
"""
def fetch_commit(commit_sha=''):
    
    # initiate Github with given user and repos
    gh = Github(login='993273596@qq.com', password='nx153156', user=myUtil.USER, repo=myUtil.REPOS)

    # initiate csvfile which store the commit info
    # csvfile = file('commit_mongodb_mongo.csv', 'wb')
    fetch = file(myUtil.FETCH_FILE_NAME, 'wb')
    fetch_writer = csv.writer(fetch)

    # write table title (3:change_type, 4:log_statement, \
    # 5:old log_loc, 6:old_store_name, 7: new log_loc 8:new_store_name)
    # """" append or not
    fetch_writer.writerow(myUtil.FETCH_TITLE)
    # """
    # fetch all the commits of given repos
    commits = gh.repos.commits.list(sha=commit_sha)
    total_file = 0
    total_cpp = 0
    total_log_cpp = 0
    total_commit = 0
    for commit in commits.iterator():
        # invoke the deal_commit function
        total_log_cpp, total_cpp, total_file = deal_commit \
                            (gh, commit.sha, total_log_cpp, total_cpp, total_file, fetch_writer)
        total_commit += 1
        if total_file % 10 == 0:
            print 'total commit is %d ; now have deal with %d none cpp file ; find cpp %d file ; \
                have saved %d file' %(total_commit, total_file, total_cpp, total_log_cpp)
    # deal_commit(gh, commit_sha, writer)

    # close the commit file
    fetch_writer.close()

"""
main function
"""
if __name__ == "__main__":
    # several configuration constant: user, repos
    # user = 'mongodb'
    # repos = 'mongo'
    # user = 'torvalds'
    # repos = 'linux'

    commit_sha = '67a7dcef45fef6172514d6df1bea3ca94a04735a'

    # with function to retieve all the commits of given path
    fetch_commit(commit_sha)

