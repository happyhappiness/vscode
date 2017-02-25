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
@ param  commit sha sha, changed cpp file file, stored file name store_name, csv writer writer
@ return bool has log (whether this patch contained log or not)
@ callee ..
@ caller  deal_commit(gh, sha, writer) ..
@ involve deal with patch file and save commit info (just store and analyze +)
"""
def deal_patch(sha, message, changed_file, store_name, writer):
    
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

    line_count = 0 # line of log statement
    # deal with each line of patch
    for line in patch:

        # filter out the one with log statement changes
        log_function = 'assert|log|debug|print|write|error'
        pattern_log = '^(-|\+)(.*(?:'+ log_function + ')[\w]*[\d]*)\((.*)$'
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
            change_type = is_log_change.group(1).strip()
            data_row.append(change_type)
            # log_statement
            log_statement = is_log_change.group().strip()
            log_statement = log_statement[1:].strip()
            data_row.append(log_statement)
            # change type with - is not dealed and write back without context info
            if change_type == '-':
                # writer.writerow(data_row)
                patch_delete[line_count] = 1 # mark to be delete change
                line_count = line_count + 1
                continue
            # backtrace to find the changed location in source file
            has_log = True
            line_back = line_count
            line_delete = 0
            while line_back != 0:
                line_back = line_back - 1 # start from the line above
                line_delete = line_delete + patch_delete[line_back] # line deleted
                # line number of description
                log_loc = re.match('^@@.*\+(.*),.*@@', patch[line_back])
                if log_loc:
                    # source file is the changed file -> loc depends on +(num)
                    # and distance of line_count and line_back except deleted lines
                    log_loc = int(log_loc.group(1)) + (line_count - line_back - 1 - line_delete)
                    data_row.append(log_loc)
                    data_row.append(store_name)
                    writer.writerow(data_row)
                    # stop search and switch to next line
                    break

        # increment line_count
        line_count = line_count + 1
    
    return has_log

"""
@ param  github parameters gh and sha of commit and the counter for stored files and fileWriter
@ return file_count new counter of stored files 
@ callee deal_patch( sha, file, writer)
@ caller fetch_commit(user, repos, commit_sha='') ..
@ involve deal with commit and involved changed file
"""
def deal_commit(gh, sha, file_count, writer):

    # retrieve info of commit with given sha
    commit = gh.repos.commits.get(sha=sha)
    message = commit.commit.message

    # save commit patch according to files
    for changed_file in commit.files:

        # filter to just deal with cpp and c files
        is_cpp = re.search('(.cpp|.c)$', changed_file.filename, re.I)
        if is_cpp:

            # write to temp file
            store_name = 'download/' + user + '_' + repos + str(file_count) + '.cpp'
            # call deal_patch to deal with the patch file
            has_log = deal_patch(sha, message, changed_file, store_name, writer)
            if has_log:
                # download the blob of file
                source = gh.git_data.blobs.get(changed_file.sha).content
                # decode to retrieve the source file
                source = base64.b64decode(source)
                temp_file = open(store_name, 'wb')
                temp_file.write(source)
                temp_file.close()
                # increment the file count
                file_count = file_count + 1

        else:
            print "not cpp"

    return file_count


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

    # write table title (3:change_type, 4:log_statement, 5:log_loc, 6:store_name)
    fetch_writer.writerow(['commit_sha', 'commit_message', 'file_name', \
                        'change_type', 'log_statement', 'log_loc', 'store_name'])

    # fetch all the commits of given repos
    commits = gh.repos.commits.list()
    file_count = 1
    for commit in commits.iterator():
        # invoke the deal_commit function
        file_count = deal_commit(gh, commit.sha, file_count, fetch_writer)
        if file_count % 10 == 0:
            print 'now saved the no. %d file' %file_count
    # deal_commit(gh, commit_sha, writer)

    # close the commit file 
    fetch_writer.close()

"""
main function
"""

# several configuration constant: user, repos
user = 'mongodb'
repos = 'mongo'

commit_sha = 'a7e74d56036e94c3e4ed11ceeb4cd43e95209aa5'

# with function to retieve all the commits of given path
fetch_commit(user, repos, commit_sha)

