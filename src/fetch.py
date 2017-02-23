#-*-coding: utf-8 -*-
from pygithub3 import Github
import csv
import sys
import re
import commands
import base64

"""
@ param  commit sha sha, changed cpp file file, stored file name store_name, csv writer writer
@ return nothing
@ callee ..
@ caller  deal_commit(gh, sha, writer) ..
@ involve deal with patch file and save commit info
"""
def deal_patch(sha, message, changed_file, store_name, writer):
    # divide mutiline string into single lines
    patch = changed_file.patch.split('\n')
    # array to record the deleted changed lines
    patch_delete = [0 for i in range(len(patch))]

    line_count = 0 # line of log statement
    # deal with each line of patch
    for line in patch:

        # filter out the none log statement changes
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
                writer.writerow(data_row)
                patch_delete[line_count] = 1 # mark to be delete change
                line_count = line_count + 1
                continue
            # backtrace to find the changed location in source file
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

        # increment line_count
        line_count = line_count + 1

"""
@ param  github parameters gh and sha of commit and fileWriter
@ return nothing 
@ callee deal_patch( sha, file, writer)
@ caller fetch_commit(user, repos, commit_sha='') ..
@ involve deal with commit and involved changed file
"""
def deal_commit(gh, sha, writer):

    # retrieve info of commit with given sha
    commit = gh.repos.commits.get(sha=sha)
    message = commit.commit.message

    # save commit patch according to files
    for changed_file in commit.files:

        # filter to just deal with cpp and c files
        is_cpp = re.search('(.cpp|.c)$', changed_file.filename, re.I)
        if is_cpp and (changed_file.changes > 0):

            # download the blob of file
            source = gh.git_data.blobs.get(changed_file.sha).content
            # decode to retrieve the source file
            source = base64.b64decode(source)
            # write to temp file
            store_name = 'download/' + user + repos + '.cpp'
            temp_file = open(store_name, 'wb')
            temp_file.write(source)
            temp_file.close()

            # call deal_patch to deal with the patch file
            deal_patch(sha, message, changed_file, store_name, writer)
        else:
            print "not cpp"



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
    csvfile = file('data/fetch_' + user + repos + '.csv', 'wb')
    writer = csv.writer(csvfile)

    # write table title (4:change_type,5:log_loc, 6:store_name)
    writer.writerow(['commit_sha','commit_message', 'file_name', \
                        'change_type', 'log_statement', 'log_loc', 'store_name'])

    # fetch all the commits of given repos
    commits = gh.repos.commits.list()
    count = 1
    for commit in commits.iterator():
        if count % 10 == 0:
            print ('now proccessing the no. %d commit' %count)
        # invoke the deal_commit function
        deal_commit(gh, commit.sha, writer)
        count = count + 1;
    # deal_commit(gh, commit_sha, writer)

    # close the commit file 
    csvfile.close()

"""
main function
"""

# several configuration constant: user, repos
user = 'mongodb'
repos = 'mongo'

commit_sha = 'a7e74d56036e94c3e4ed11ceeb4cd43e95209aa5'

# with function to retieve all the commits of given path
fetch_commit(user, repos, commit_sha)

