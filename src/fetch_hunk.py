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
    if is_cpp:
        return True
    else:
        return False


"""
@ param  patch info, patch, hunk counter, csv writer
@ return bool has log and updated hunk counter
@ involve deal with patch file and save hunk info(has log)
"""
def deal_patch( patch_file, log_function, total_hunk, writer, caller_flag):

    full_patch_file = open(my_constant.PATCH_DIR + patch_file, 'rb')
    patch = full_patch_file.readlines()
    has_log = False

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

    # deal with each line of patch
    for line in patch:
        # recognize change hunk by description info
        is_hunk = re.match(r'^@@.*-(.*),.*\+(.*),.*@@', line)
        # deal with past hunk and record new one
        if is_hunk:
            # if has log update, so deal with it
            if len(old_log_loc) != 0 or len(new_log_loc) != 0:
                has_log = True
                total_hunk += 1
                # write old hunk file to temp file
                old_hunk_name = my_constant.DOWNLOAD_OLD_HUNK + str(total_hunk) + '.cpp'
                myUtil.save_file(old_hunk, old_hunk_name)

                # write new hunk file to temp file
                new_hunk_name = my_constant.DOWNLOAD_NEW_HUNK + str(total_hunk) + '.cpp'
                myUtil.save_file(new_hunk, new_hunk_name)

                writer.writerow([patch_file, old_file, new_file, old_hunk_name, new_hunk_name, \
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
        # decide if it belongs to log change
        is_log_change = re.search(log_function, line, re.I)
        if change_type != '-':
            new_hunk += (line[1:]) + caller_flag
            if is_log_change:
                new_log_loc.append(new_loc)
            new_loc += 1
        if change_type != '+':
            old_hunk += (line[1:]) + caller_flag
            if is_log_change:
                old_log_loc.append(old_loc)
            old_loc += 1

    # deal with last hunk, if has log update
    if len(old_log_loc) != 0 or len(new_log_loc) != 0:
        has_log = True
        total_hunk += 1
        # write old hunk file to temp file
        old_hunk_name = my_constant.DOWNLOAD_OLD_HUNK + str(total_hunk) + '.cpp'
        myUtil.save_file(old_hunk, old_hunk_name)

        # write new hunk file to temp file
        new_hunk_name = my_constant.DOWNLOAD_NEW_HUNK + str(total_hunk) + '.cpp'
        myUtil.save_file(new_hunk, new_hunk_name)

        writer.writerow(patch_info + [old_hunk_name, new_hunk_name, \
        old_hunk_loc, new_hunk_loc, json.dumps(old_log_loc), json.dumps(new_log_loc)])

    full_patch_file.close()
    return has_log, total_hunk

"""
@ param
@ return
@ involve read patch from repos patch dir and deal with each patch file
"""
def fetch_patch():

    # filter out the one with log statement changes
    log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)
    log_function = myUtil.functionToRegrexStr(log_functions)

    # initiate csvfile
    hunk_file = file(my_constant.FETCH_HUNK_FILE_NAME, 'wb')
    hunk_writer = csv.writer(hunk_file)
    hunk_writer.writerow(my_constant.FETCH_HUNK_TITLE)

    patch_files = commands.getoutput('ls ' + my_constant.PATCH_DIR)
    patch_files = patch_files.split('\n')
    total_hunk = 0
    for curr_patch_file in patch_files:
        print 'now processing patch %s' %curr_patch_file
        total_hunk = deal_patch(curr_patch_file, log_function, total_hunk, hunk_writer, '')

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

    # sha = 'a0f91f1daa7765066a784e4479da7e231374a065'
    # cmake
    # fetch_commit(False, 'b59987eed9f5a67b6672d913501e3ce6495f1465', 98892, 49199, 774, 1476)
    # xgboost
    # 'ece5f00ca152bd56df5579e2ca76372fbf04dc38', 13313, 2366, 568, 912
    # redis
    # fetch_commit(False, 'ed9b544e10b84cd43348ddfab7068b610a5df1f7', 14980, 9089, 2364, 4581)
    fetch_patch()
    # fetch_commit()
    # re.match(r'^@@.*-(.*),.*\+(.*),.*@@', 'test statement')
    # log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)
    # log_function = myUtil.functionToRegrexStr(log_functions)
    # is_log_change = re.search(log_function, 'printf', re.I)
    # if is_log_change:
    #     print 'ok'
    # filter_commit(gh, commit_sha)
    # deal with hunk
