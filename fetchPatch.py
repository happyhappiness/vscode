#!/usr/bin/python
#-*-coding: utf-8 -*-

from pygithub3 import Github
import csv
import sys

reload(sys)
sys.setdefaultencoding('utf-8')

"""
@ param  github parameters gh and sha of commit and fileWriter
@ return nothing 
@ involve deal with patch file and save commit info
"""
def deal_commit(gh, sha, writer):
    
    # retrieve info of commit with given sha
    commit = gh.repos.commits.get(sha=sha)

    # initiate the data for this commit
    data_row = []
    # commit sha
    data_row.append(commit.sha)
    # commit html
    data_row.append(commit.html_url)
    # commit message
    data_row.append(commit.commit.message)
    # commit author
    # data_row.append(commit.commiter.login)
    # data_row.append(commit.committer.id)     
    # commit changes statistics
    data_row.append(commit.stats.additions)
    data_row.append(commit.stats.deletions)

    # save commit patch according to files
    for changedfile in commit.files:
        # info about file : filename and urls 
        data_row.append(changedfile.filename)
        # data_row.append(changedfile.sha)
        # data_row.append(changedfile.blob_url)
        raw_url = changedfile.blob_url
        raw_url = raw_url.replace('github', 'raw.githubusercontent')
        raw_url = raw_url.replace('blob/', '') 
        data_row.append(raw_url)
        # # download the blob of file
        # data = gh.git_data.blobs.get(changedfile.sha).content
        # # decode to retrieve the source file
        # info = base64.b64decode(data)        
       
        # info about patch
        # data_row.append(changedfile.patch)
        # print changedfile.patch
        data_row.append(changedfile.additions)
        data_row.append(changedfile.deletions)
        
    # write back to file
    writer.writerow(data_row)


"""
@ param  configuration parameters like user, repos and start_sha
@ return flag 
@ involve save commit info of given repos
"""
def fetch_commit(user, repos):
    
    # initiate Github with given user and repos 
    gh = Github(login='993273596@qq.com', password='nx153156', user=user, repo=repos)
    # initiate csvfile which store the commit info
    csvfile = file('commit_mongodb_mongo.csv', 'wb')
    writer = csv.writer(csvfile)
    # write the table header
    # writer.writerow([ 'sha', 'url', 'message', 'author', 'authorId', 'additions', 'deletions', 'fileInfo'])
    writer.writerow([ 'sha', 'url', 'message', 'additions', 'deletions', 'fileInfo'])

    # fetch all the commits of given repos
    commits = gh.repos.commits.list()
    count = 1
    for commit in commits.iterator():
        if count % 10 == 0:
            print ('now proccessing the no. %d commits' %count)
        # invoke the deal_commit function
        deal_commit(gh, commit.sha, writer)
        count = count + 1;

    # close the commit file 
    csvfile.close()

"""
main function
"""

# several configuration constant: user, repos
user = 'mongodb'
repos = 'mongo'

# with function to retieve all the commits of given path
fetch_commit(user, repos)

