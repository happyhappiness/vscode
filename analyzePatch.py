#-*-coding: utf-8 -*-

from pygithub3 import Github
import csv
import sys
import re

# reload(sys)
# sys.setdefaultencoding('utf-8')

"""
@ param  github parameters gh and sha of commit and fileWriter
@ return nothing 
@ involve deal with patch file and save commit info
"""
def deal_commit(gh, sha, writer):
    
    # retrieve info of commit with given sha
    commit = gh.repos.commits.get(sha=sha)
    message = commit.commit.message

    # save commit patch according to files
    for changedfile in commit.files:
        file_name = changedfile.filename

        # filter to just deal with cpp and c files
        is_cpp = re.search('(.cpp|.c)$', file_name, re.I)
        if(is_cpp):
            
            file_url = changedfile.blob_url
            file_url = file_url.replace('github', 'raw.githubusercontent')
            file_url = file_url.replace('blob/', '') 
            # # download the blob of file
            # data = gh.git_data.blobs.get(changedfile.sha).content
            # # decode to retrieve the source file
            # info = base64.b64decode(data)   
            
            # divide mutiline string into single lines 
            patch = changedfile.patch.split('\n')
              
            line_count = 0
            # deal with each line of patch
            for line in patch:
                
                # filter out the none log statement changes
                log_function = 'assert|log|debug|print|write|error'
                pattern_log = '^(-|\+)(.*(?:'+ log_function + ')[\w]*[\d]*)\((.*)$';
                is_log_change = re.match(pattern_log, line, re.I)
                if(is_log_change):
                    
                    # store this changed log statement
                    data_row = []
                    # commit sha
                    data_row.append(sha)
                    # commit message
                    data_row.append(message)
                    # file name
                    data_row.append(file_name)
                    # file sha
                    data_row.append(changedfile.sha)
                    # file url
                    data_row.append(file_url)
                    # log_statement
                    data_row.append(is_log_change.group())
                    # change_type
                    data_row.append(is_log_change.group(1).strip())
                    # log_function 
                    data_row.append(is_log_change.group(2).strip())
                    # log parameters after removing some symbols
                    log_params = is_log_change.group(3).split(',|)|;')
                    data_row.append(log_params)
                    # log location
                    # backtrace to find the location
                    line_back = line_count
                    while(line_back != 0):
                        line_back = line_back - 1
                        log_location = re.match('^@@.*\+(.*),.*@@', patch[line_back])
                        if(log_location):
                            log_location = int(log_location.group(1)) + line_count
                            data_row.append(log_location)
                            break             
                        
                    # write back to file
                    writer.writerow(data_row)

                # increment line_count
                line_count = line_count + 1
        else:
            print "not cpp"
        


"""
@ param  configuration parameters like user, repos and start_sha
@ return flag 
@ involve save commit info of given repos
"""
def fetch_commit(user, repos, commit_sha=''):
    
    # initiate Github with given user and repos 
    gh = Github(login='993273596@qq.com', password='xx', user=user, repo=repos)

    # initiate csvfile which store the commit info
    # csvfile = file('commit_mongodb_mongo.csv', 'wb')
    csvfile = file('analyze_patch_mongodb_mongo.cvs', 'wb')
    writer = csv.writer(csvfile)

    # write table title 
    writer.writerow([ 'commit_sha','commit_message', 'file_name', 'file_sha', 'file_url', 'log_statement', 'change_type', 'log_function', 'log_params','log_location'])

    # # fetch all the commits of given repos
    commits = gh.repos.commits.list()
    count = 1
    for commit in commits.iterator():
        if count % 10 == 0:
            print ('now proccessing the no. %d commits' %count)
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

