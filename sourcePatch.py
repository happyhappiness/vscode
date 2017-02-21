#-*-coding: utf-8 -*-
from pygithub3 import Github
import csv
import sys
import re
import commands
import base64

# reload(sys)
# sys.setdefaultencoding('utf-8')
"""
@ param  string array arr and begin index(include) and end index(not include) 
@ return string by concanating element from begin to end index 
@ involve concanate string element of array
"""
def conca_element(arr, begin, end):
    conca_str = ''
    for i in range(begin, end):
        conca_str = conca_str + arr[i] + '\n'
    return conca_str

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
        if(is_cpp and (changedfile.changes > 0)):
            
            # file_url = changedfile.blob_url
            # file_url = file_url.replace('github', 'raw.githubusercontent')
            # file_url = file_url.replace('blob/', '') 
            # download the blob of file
            source = gh.git_data.blobs.get(changedfile.sha).content
            # decode to retrieve the source file
            source = base64.b64decode(source)   
            # # remove some statement for further analyze
            # source_modified = re.sub('#.*', ' ', source)
            # source_modified = re.sub('using .*', ' ', source_modified)
            # source_modified = re.sub('[a-zA-Z0-9]*::', ' ', source_modified)
            # write to temp file
            temp_file = open('data/temp.cpp','wb')
            temp_file.write(source)
            temp_file.close()
            
            # divide mutiline string into single lines 
            patch = changedfile.patch.split('\n')
            patch_delete = [0 for i in range(len(patch))]
              
            line_count = 0 # line of log statement
            # deal with each line of patch
            for line in patch:
                
                # filter out the none log statement changes
                log_function = 'assert|log|debug|print|write|error'
                pattern_log = '^(-|\+)(.*(?:'+ log_function + ')[\w]*[\d]*)\((.*)$';
                is_log_change = re.match(pattern_log, line, re.I)
                if(is_log_change):
                    
                    # store this changed log statement
                    data_row = []
                    # # commit sha
                    # data_row.append(sha)
                    # commit message
                    data_row.append(message)
                    # file name
                    data_row.append(file_name)
                    # # file sha
                    # data_row.append(changedfile.sha)
                    # # file url
                    # data_row.append(file_url)
                    # change_type
                    change_type = is_log_change.group(1).strip()
                    data_row.append(change_type)
                    # log_statement
                    log_statement = is_log_change.group().strip()
                    log_statement = log_statement[1:].strip()
                    data_row.append(log_statement)
                    # change type with - is not dealed and write back without context info
                    if(change_type == '-'):                        
                        writer.writerow(data_row)
                        patch_delete[line_count] = 1
                        line_count = line_count + 1
                        continue
                    # # log_function 
                    # data_row.append(is_log_change.group(2).strip())
                    # # log parameters after removing some symbols
                    # log_params = is_log_change.group(3).split(',|)|;')
                    # data_row.append(log_params)
                    # log location
                    # backtrace to find the location and further retrieve the context
                    line_back = line_count
                    line_delete = 0
                    while(line_back != 0):
                        line_back = line_back - 1 
                        line_delete = line_delete + patch_delete[line_back] # line deleted
                        log_loc = re.match('^@@.*\+(.*),.*@@', patch[line_back]) # line number of description
                        if(log_loc):
                            log_loc = int(log_loc.group(1)) + (line_count - line_back - 1 - line_delete)
                            loc_info = commands.getoutput('cat data/temp.cpp | xargs -0 find-func-decls ' + str(log_loc))
                            loc_info = loc_info.split('@')
                            # formal output should be array with len = 4
                            Loc_info_len = len(loc_info)
                            if (Loc_info_len >= 4):                                
                                if (isinstance(source, str)):
                                    source = source.split('\n');
                                # loc info
                                start_loc = int(log_loc[Loc_info_len - 3])
                                end_loc = int(log_loc[Loc_info_len - 2])
                                # whole context
                                context = conca_element(source, start_loc - 1, end_loc)
                                data_row.append(context)
                                # upper context(no log)
                                log_loc = context.find(log_statement)
                                # break if wrong context
                                if(log_loc == -1):
                                    break
                                context_up = context[0:log_loc - 1]
                                data_row.append(context_up)
                                # downer context(no log)
                                log_loc = context.find('\n', log_loc)
                                # break if wrong context
                                if(log_loc == -1):
                                    break
                                context_down = context[log_loc + 1:]
                                data_row.append(context_down)
                                # write back to file if get useful context
                                writer.writerow(data_row)
                                # data_row.append(log_loc) # corresponding location in context
                                break             
                        
                    # # write back to file
                    # writer.writerow(data_row)

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
    gh = Github(login='993273596@qq.com', password='nx153156', user=user, repo=repos)

    # initiate csvfile which store the commit info
    # csvfile = file('commit_mongodb_mongo.csv', 'wb')
    csvfile = file('data/source_patch_mongodb_mongo.csv', 'wb')
    writer = csv.writer(csvfile)

    # write table title 
    writer.writerow([ 'commit_message', 'file_name', 'log_statement', 'change_type', 'context_info'])

    # fetch all the commits of given repos
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

