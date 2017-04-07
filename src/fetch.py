#-*-coding: utf-8 -*-
from pygithub3 import Github
import csv
import sys
import re
import commands
import base64

reload(sys);
sys.setdefaultencoding('utf8')

"""
@ param  patch, line_count of the changed log, patch_delete array and type of this change
@ return log_loc
@ callee ..
@ caller deal_patch(sha, message, changed_file, old_store_name, new_store_name, writer)
@ involve get log location based on its location in patch and patch info
"""
def get_loc(patch, line_count, patch_delete, patch_add, change_type):
    
    line_back = line_count
    line_delete = 0
    line_add = 0
    while line_back != -1:
        line_back = line_back - 1 # start from the line above
        line_delete = line_delete + patch_delete[line_back] # line deleted
        line_add = line_add + patch_add[line_back] # line added
        # line number of description
        log_loc = re.match('^@@.*-(.*),.*\+(.*),.*@@', patch[line_back])
        if log_loc:
            if change_type == '-':
                log_loc = int(log_loc.group(1)) + (line_count - line_back - 1 - line_add)
            else:
                # source file is the changed file -> loc depends on +(num)
                # and distance of line_count and line_back except deleted lines
                log_loc = int(log_loc.group(2)) + (line_count - line_back - 1 - line_delete)
            break

    return log_loc

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

    # array to record the deleted changed lines
    patch_delete = [0 for i in range(len(patch))]
    patch_add = [0 for i in range(len(patch))]

    line_count = 0 # line of log statement
    # deal with each line of patch
    for line in patch:

        # use start character yto judge change type
        change_type = line[0]
        if change_type == '-':
            patch_delete[line_count] = 1 # mark to be delete change
        else:
            if change_type == '+':
                patch_add[line_count] = 1 # mark to be add change
            else:
                # no change so no log change: increment line_count and continue
                line_count = line_count + 1
                continue

        # filter out the one with log statement changes
        log_function = 'assert|log|debug|print|write|error'
        pattern_log = '^(-|\+)([^/]*(?:'+ log_function + ')[\w]*[\d]*)\((.*)$'
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
            # change_type = is_log_change.group(1).strip()
            data_row.append(change_type)
            # log_statement
            log_statement = is_log_change.group().strip()
            log_statement = log_statement[1:].strip()
            data_row.append(log_statement)
            # change type with - is not dealed and write back without context info
            # backtrace to find the changed location in source file
            has_log = True
            # call get_loc to retrieve the changed log location in files
            log_loc = get_loc(patch, line_count, patch_delete, patch_add, change_type)
            if log_loc:
                # source file is the changed file -> loc depends on +(num)
                # and distance of line_count and line_back except deleted lines
                data_row.append(log_loc)
                data_row.append(old_store_name)
                data_row.append(new_store_name)
                writer.writerow(data_row)

        # increment line_count
        line_count = line_count + 1

    return has_log

"""
@ param  github parameters gh and sha of commit and the counter for stored/total files and fileWriter
@ return file_count new counter of stored files, total_count counters of cpp files
@ callee deal_patch( sha, file, writer)
@ caller fetch_commit(user, repos, commit_sha='') ..
@ involve deal with commit and involved changed file
"""
def deal_commit(gh, sha, file_count, total_count, writer):

    # retrieve info of commit with given sha
    commit = gh.repos.commits.get(sha=sha)
    message = commit.commit.message

    # save commit patch according to files
    for changed_file in commit.files:

        # filter to just deal with cpp and c files
        is_cpp = re.search('(.cpp|.c|.cc)$', changed_file.filename, re.I)
        # filter to not deal with test module files
        is_test_cpp = re.search('(test.cpp|test.c)$', changed_file.filename, re.I)
        if is_cpp and not is_test_cpp:
            # increment the total file count
            total_count = total_count + 1

            # define old/new_store_name
            new_store_name = '/data/download/' + repos + '/' + user + '_' + repos + str(file_count) + '_new.cpp'
            old_store_name = '/data/download/' + repos + '/' + user + '_' + repos + str(file_count) + '_old.cpp'

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
                file_count = file_count + 1

        else:
            print "not cpp without test"

    return file_count, total_count


"""
@ param  configuration parameters like user, repos and start_sha
@ return nothing 
@ callee deal_commit(gh, sha, writer)
@ caller main ..
@ involve save commit info of given repos
"""
def fetch_commit(user, repos, commit_sha=''):
    
    # initiate Github with given user and repos 
    gh = Github(login='993273596@qq.com', password='nx153156', user=user, repo=repos)

    # initiate csvfile which store the commit info
    # csvfile = file('commit_mongodb_mongo.csv', 'wb')
    fetch = file('data/fetch_' + user + '_' + repos + '.csv', 'wb')
    fetch_writer = csv.writer(fetch)

    # write table title (3:change_type, 4:log_statement, 5:log_loc, 6:old_store_name, 7:new_store_name)
    fetch_writer.writerow(['commit_sha', 'commit_message', 'file_name', \
                        'change_type', 'log_statement', 'log_loc', 'old_store_name', 'new_store_name'])

    # fetch all the commits of given repos
    commits = gh.repos.commits.list()
    file_count = 0
    total_count = 0
    for commit in commits.iterator():
        # invoke the deal_commit function
        file_count, total_count = deal_commit(gh, commit.sha, file_count, total_count, fetch_writer)
        if file_count % 10 == 0:
            print 'now saved the no. %d file, total file is %d' %(file_count, total_count)
    # deal_commit(gh, commit_sha, writer)

    # close the commit file
    fetch_writer.close()

"""
main function
"""

# several configuration constant: user, repos
# user = 'mongodb'
# repos = 'mongo'
# user = 'opencv'
# repos = 'opencv'
# user = 'apple'
# repos = 'swift'
# user = 'llvm-mirror'
# repos = 'clang'
user = 'torvalds'
repos = 'linux'

commit_sha = 'a7e74d56036e94c3e4ed11ceeb4cd43e95209aa5'

# with function to retieve all the commits of given path
fetch_commit(user, repos, commit_sha)

