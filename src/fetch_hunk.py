#-*-coding: utf-8 -*-
"""
input: USER, REPOS
BY: commit -> patch
output: hunk records
hunk info [commit info, patch info, ...]
"""
import csv
import sys
import re
import commands
import base64
import json
from pygithub3 import Github
from itertools import islice
import my_constant
import myUtil

reload(sys);
sys.setdefaultencoding('utf8')

"""
@ param  patch info, patch, hunk counter, csv writer
@ return bool has log and updated hunk counter
@ involve deal with patch file and save hunk info(has log)
"""
def deal_patch(patch_info, patch, total_hunk, writer):

    has_log = False
    # divide mutiline string into single lines
    patch = patch.split('\n')

    # old and new hunk content
    old_hunk = ''
    new_hunk = ''
    # old and new file location of hunk top
    old_hunk_loc = 0
    new_hunk_loc = 0
    old_loc = 0
    new_loc = 0
    # old and new log locations
    old_log_loc = [] # mov, del, update
    new_log_loc = [] # ins
    # filter out the one with log statement changes
    log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)
    log_function = myUtil.functionToRegrexStr(log_functions)

    # deal with each line of patch
    for line in patch:
        # recognize change hunk by description info
        is_hunk = re.match(r'^@@.*-(.*),.*\+(.*),.*@@', line)
        # deal with past hunk and record new one
        if is_hunk:
            # if has log update, so deal with it
            if not len(old_log_loc) == 0:
                has_log = True
                total_hunk += 1
                # write old hunk file to temp file
                old_hunk_name = my_constant.DOWNLOAD_OLD_HUNK + str(total_hunk) + '.cpp'
                myUtil.save_file(old_hunk, old_hunk_name)

                # write new hunk file to temp file
                new_hunk_name = my_constant.DOWNLOAD_NEW_HUNK + str(total_hunk) + '.cpp'
                myUtil.save_file(new_hunk, new_hunk_name)

                writer.writerow(patch_info + [ old_hunk_name, new_hunk_name, old_hunk, new_hunk, \
                old_hunk_loc, new_hunk_loc, json.dumps(old_log_loc), json.dumps(new_log_loc)])
            # initialize hunk info
            old_hunk = ''
            new_hunk = ''
            old_hunk_loc = is_hunk.group(1)
            new_hunk_loc = is_hunk.group(2)
            old_loc = 0
            new_loc = 0
            old_log_loc = [] # mov, del, update
            new_log_loc = [] # ins
            continue

        # record change type flag
        change_type = line[0]
        if change_type != '-':
            new_hunk += (line[1:]) + '\n'
        if change_type != '+':
            old_hunk += (line[1:]) + '\n'
            # decide if it belongs to log change
            is_log_change = re.search(log_function, line, re.I)
            if is_log_change:
                old_log_loc.append(old_loc)
            old_loc += 1
    return has_log, total_hunk


"""
@ param gh and sha
@ return commit, message
@ involve filter out commit which has dealed before (sha, file number, file name)
"""
def filter_commit(gh, sha):

    # commit info
    commit = gh.repos.commits.get(sha=sha)
    message = commit.commit.message

    # has brother[multiline]
    is_has_brother = re.search(r'\n([0-9a-fA-F]{6,})\s', message, re.M)
    # do not deal with top ones
    if is_has_brother:
        return None, None
    else:
        # deal to get issue number
        issue_numbers = re.findall(r'#(\d{4,})', message, re.M)
        issue_addresses = []
        for issue_number in issue_numbers:
            issue_addresses.append(my_constant.ISSUE_ADDRESS + issue_number)
        commit_info = [sha, message, issue_addresses]

        return commit, commit_info

"""
@ param gh and sha
@ return flag
@ involve filter out file which is not cpp like
"""
def filter_file(changed_file):

    # cpp like(ignore case)
    is_cpp = re.search(my_constant.FILE_FORMAT, changed_file.filename, re.I)
    # test like
    # is_test_cpp = re.search(r'(test)$', changed_file.filename, re.I)
    # modified
    change_type = changed_file.status
    if is_cpp and change_type == 'modified':
        return True
    else:
        return False

"""
@ param gh and sha and four counters and fileWriter
@ return total hunk, total_log_cpp, total_cpp and total file 
@ involve deal with commit and involved changed file
"""
def deal_commit(gh, sha, total_hunk, total_log_cpp, total_cpp, total_file, writer):

    # filter sha by message and retrieve info if pass
    commit, commit_info = filter_commit(gh, sha)
    if commit is not None:
        # deal with changed file and save patch with log modifications
        for changed_file in commit.files:

            total_file += 1
            # filter file to choose the modified cpp like file
            is_ok = filter_file(changed_file)
            if is_ok:
                # increment the total file count
                total_cpp = total_cpp + 1

                # old/new_store_name
                old_store_name = my_constant.DOWNLOAD_OLD_FILE + str(total_log_cpp) + '.cpp'
                new_store_name = my_constant.DOWNLOAD_NEW_FILE + str(total_log_cpp) + '.cpp'
                # patch info
                patch_info = commit_info + [changed_file.filename, old_store_name, new_store_name]
                try:
                    patch = changed_file.patch
                except AttributeError as e:
                    print e
                    continue
                # call deal_patch to deal with the patch file
                has_log, total_hunk = deal_patch(patch_info, patch, total_hunk, writer)
                if has_log:
                    # increment the file count
                    total_log_cpp += 1

                    # download the blob of file
                    source = gh.git_data.blobs.get(changed_file.sha).content
                    # decode to retrieve the source file
                    source = base64.b64decode(source)

                    # write new file to temp file
                    myUtil.save_file(source, new_store_name)

                    # write patch file to temp file
                    patch_store_name = 'second/download/temp.cpp'
                    myUtil.save_file(changed_file.patch, patch_store_name)

                    # get old file with patch cmd and write back
                    output = commands.getoutput('patch -R ' + new_store_name \
                            + ' -i ' + patch_store_name + ' -o ' + old_store_name)
                    output = commands.getoutput('rm ' + patch_store_name)


    return total_hunk, total_log_cpp, total_cpp, total_file


"""
@ param  configuration parameters like user, repos and start_sha
@ return nothing 
@ involve fetch and analyze each commit and save hunk that has log
"""
def fetch_commit(isFromStart=True, commit_sha='', start_file=0, start_cpp=0, start_log_cpp=0, start_hunk=0):

    # initiate Github with given user and repos
    gh = Github(login='993273596@qq.com', password='nx153156', user=my_constant.USER, repo=my_constant.REPOS)

    # initiate csvfile which store the commit info
    if isFromStart:
        hunk_file = file(my_constant.FETCH_HUNK_FILE_NAME, 'wb')
        hunk_writer = csv.writer(hunk_file)
        hunk_writer.writerow(my_constant.FETCH_HUNK_TITLE)
    else:
        hunk_file = file(my_constant.FETCH_HUNK_FILE_NAME, 'ab')
        hunk_writer = csv.writer(hunk_file)

    # fetch all the commits of given repos
    commits = gh.repos.commits.list(sha=commit_sha)
    total_file = start_file
    total_cpp = start_cpp
    total_log_cpp = start_log_cpp
    total_hunk = start_hunk
    for commit in commits.iterator():
        # call deal_commit function to deal with each commit
        total_hunk, total_log_cpp, total_cpp, total_file = deal_commit \
                            (gh, commit.sha, total_hunk, total_log_cpp, total_cpp, total_file, hunk_writer)
        if total_file % 10 == 0:
            print 'now have deal with %d file ; find cpp %d file ;\
have saved %d log cpp file, %d hunk' %(total_file, total_cpp, total_log_cpp, total_hunk)
    print "end of commit"
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

    sha = 'a0f91f1daa7765066a784e4479da7e231374a065'
    # with function to retieve all the commits of given path
    fetch_commit(False, sha, 0, 0, 376, 710)

    # re.match(r'^@@.*-(.*),.*\+(.*),.*@@', 'test statement')
    # log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)
    # log_function = myUtil.functionToRegrexStr(log_functions)
    # is_log_change = re.search(log_function, 'printf', re.I)
    # if is_log_change:
    #     print 'ok'
    # filter_commit(gh, commit_sha)
    # deal with hunk
