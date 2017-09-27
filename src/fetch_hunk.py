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
@ param old and new hunk, hunk counter
@ return hunk counter, old and new hunk
@ involve store hunk file
"""
def store_hunk(old_hunk, new_hunk, patch_hunk, total_hunk):
    
    total_hunk += 1
    print 'now processing hunk: %d' %(total_hunk)
    # store old hunk file
    old_hunk_name = my_constant.DOWNLOAD_OLD_HUNK + str(total_hunk) + '.cpp'
    myUtil.save_file(old_hunk, old_hunk_name)

    # store new hunk file
    new_hunk_name = my_constant.DOWNLOAD_NEW_HUNK + str(total_hunk) + '.cpp'
    myUtil.save_file(new_hunk, new_hunk_name)

    # store patch hunk file
    patch_hunk_name = my_constant.DOWNLOAD_PATCH_HUNK + str(total_hunk) + '.cpp'
    myUtil.save_file(patch_hunk, patch_hunk_name)

    return total_hunk, old_hunk_name, new_hunk_name, patch_hunk_name

"""
@ param patch info, patch, log function, hunk counter and file writer
@ return hunk counter
@ involve recognize and save hunk info(has log)
"""
def deal_file_diff( version_diff_info, file_diff, log_function, total_hunk, writer):

    # old and new hunk content
    old_hunk = new_hunk = patch_hunk = ''
    # old and new file location of hunk top
    old_hunk_loc = new_hunk_loc = 0
    old_loc = new_loc = 0
    # old and new log locations
    old_log_loc = []
    new_log_loc = []

    # deal with each line of patch
    file_diff = file_diff[2:]
    for line in file_diff:
        # recognize change hunk by description info
        is_hunk = re.match(r'^@@.*-(.*),.*\+(.*),.*@@$', line)
        # deal with past hunk and record new one
        if is_hunk:
            # if has log modification
            if len(old_log_loc) != 0 or len(new_log_loc) != 0:
                total_hunk, old_hunk_name, new_hunk_name, patch_hunk_name = store_hunk(old_hunk, new_hunk, patch_hunk, total_hunk)
                writer.writerow(version_diff_info + [patch_hunk_name, old_hunk_name, new_hunk_name, \
                    old_hunk_loc, new_hunk_loc, json.dumps(old_log_loc), json.dumps(new_log_loc)])
            # initialize hunk info
            old_hunk = new_hunk = patch_hunk = ''
            old_hunk_loc = is_hunk.group(1)
            new_hunk_loc = is_hunk.group(2)
            old_loc = new_loc = 0
            old_log_loc = []
            new_log_loc = []
            continue

        # record change type flag
        change_type = line[0]
        if change_type not in ['-', '+', ' ']:
            continue
        patch_hunk += line
        line = line[1:]
        # decide if it belongs to log change
        is_log_change = re.search(log_function, line, re.I)
        # + and common
        if change_type != '-':
            new_hunk += line
            if is_log_change:
                new_log_loc.append(new_loc)
            new_loc += 1
        # - and common
        if change_type != '+':
            old_hunk += line
            if is_log_change:
                old_log_loc.append(old_loc)
            old_loc += 1

    # deal with last hunk, if has log update
    if len(old_log_loc) != 0 or len(new_log_loc) != 0:
        total_hunk, old_hunk_name, new_hunk_name, patch_hunk_name = store_hunk(old_hunk, new_hunk, patch_hunk, total_hunk)
        writer.writerow(version_diff_info + [patch_hunk_name, old_hunk_name, new_hunk_name, \
            old_hunk_loc, new_hunk_loc, json.dumps(old_log_loc), json.dumps(new_log_loc)])

    return total_hunk

"""
@ param file name
@ return flag
@ involve filter out file which is not cpp like and which is test like
"""
def filter_file(file_name):

    # cpp like(ignore case)
    is_cpp = re.search(my_constant.CPP_FILE_FORMAT, file_name, re.I)
    # test like
    is_test_cpp = re.search(r'test', file_name, re.I)
    if is_cpp and not is_test_cpp:
        return True
    else:
        return False

"""
@ param  version diff file, log function, hunk counter and file writer
@ return bool has log and updated hunk counter
@ involve recognize and deal with version diff file
"""
def deal_version_diff( version_diff_file, log_function, total_hunk, writer):

    full_version_diff_file = open(my_constant.PATCH_DIR + version_diff_file, 'rb')
    version_diff = full_version_diff_file.readlines()

    file_diff = []
    is_diff_file = False
    old_file = new_file = None
    for i in range(len(version_diff)):
        # get diff file
        is_diff = re.match(r'^diff .*', version_diff[i])
        if is_diff:
            # get old file name
            i += 1
            is_old = re.match(r'^--- (\S*)\s*.*', version_diff[i])
            if is_old:
                temp_old_file = is_old.group(1)
                # do not deal with this file diff
                if filter_file(temp_old_file):
                    # get new file name
                    i += 1
                    is_new = re.match(r'^\+\+\+ (\S*)\s*.*', version_diff[i])
                    if is_new:
                        temp_new_file = is_new.group(1)
                        # do not deal with this file diff
                        if filter_file(temp_new_file):
                            if is_diff_file:
                                    # deal with previous diff file
                                total_hunk = deal_file_diff([version_diff_file, old_file, new_file], \
                                                    file_diff, log_function, total_hunk, writer)
                                file_diff = []
                            is_diff_file = True
                            old_file = temp_old_file
                            new_file = temp_new_file
                            continue
            if is_diff_file:
                # mark end of previous diff file
                is_diff_file = False
                # deal with previous diff file
                total_hunk = deal_file_diff([version_diff_file, old_file, new_file], \
                                    file_diff, log_function, total_hunk, writer)
                file_diff = []
        # record diff file
        if is_diff_file:
            file_diff.append(version_diff[i])

    # deal with last file diff
    if is_diff_file:
        # deal with previous diff file
        total_hunk = deal_file_diff([version_diff_file, old_file, new_file], \
                                file_diff, log_function, total_hunk, writer)

    full_version_diff_file.close()
    return total_hunk

"""
@ param
@ return
@ involve read patch from repos patch dir and deal with each patch file
"""
def fetch_version_diff():

    # filter out the one with log statement changes
    log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)
    log_function = myUtil.functionToRegrexStr(log_functions)
    # print re.search(log_function, '\t   ap_log_error()')

    # initiate csvfile
    hunk_file = file(my_constant.FETCH_HUNK_FILE_NAME, 'wb')
    hunk_writer = csv.writer(hunk_file)
    hunk_writer.writerow(my_constant.FETCH_HUNK_TITLE)

    version_diff_files = commands.getoutput('ls ' + my_constant.PATCH_DIR)
    version_diff_files = version_diff_files.split('\n')
    total_hunk = 0
    for version_diff_file in version_diff_files:
        print 'now processing patch %s' %version_diff_file
        total_hunk = deal_version_diff(version_diff_file, log_function, total_hunk, hunk_writer)

    hunk_file.close()

"""
@ param
@ return
@ involve sort dir by version
"""
def compare_version_dir(version_a, version_b):
    pattern = r'.*-(\d*)\.(\d*)\.(\d*)'
    info_a = re.match(pattern, version_a)
    info_b = re.match(pattern, version_b)
    if info_a and info_b:
        info_a = info_a.groups()
        info_b = info_b.groups()
        for i in range(len(info_a)):
            if int(info_a[i]) == int(info_b[i]):
                continue
            else:
                if int(info_a[i]) > int(info_b[i]):
                    return 1
                else:
                    return -1
    else:
        print 'can not deal with %s and %s' %(version_a, version_b)
        return 0



"""
@ param
@ return
@ involve create version diff
"""
def create_version_diff():
    # clear old patch file
    clear = commands.getoutput('rm ' + my_constant.PATCH_DIR + '*')
    # get all versions
    versions = commands.getoutput('ls ' + my_constant.REPOS_DIR)
    versions = versions.split('\n')
    versions.sort(compare_version_dir)
    size = len(versions)
    for i in range(size - 1):
        print 'now creating patch for %s and %s' %(versions[i], versions[i + 1])
        patch = commands.getoutput('diff -BEr -U 6 ' + my_constant.REPOS_DIR + versions[i] + ' '\
                                + my_constant.REPOS_DIR + versions[i + 1] + ' > ' \
                                + my_constant.PATCH_DIR + versions[i] + '_diff_' + versions[i + 1])
                       
"""
main function
"""
if __name__ == "__main__":
    # create_version_diff()
    fetch_version_diff()


