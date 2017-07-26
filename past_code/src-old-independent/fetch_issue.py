#-*-coding: utf-8 -*-
from pygithub3 import Github
import csv
import sys
import re
import commands
import base64
import my_constant
import json
import myUtil
from itertools import islice

reload(sys);
sys.setdefaultencoding('utf8')

"""
@ param  configuration parameters like user, repos and start_sha
@ return nothing 
@ callee deal_commit(gh, sha, writer)
@ caller fetch_hunk
@ involve fetch and analyze each commit and save hunk info with log
"""
def deal_issue(commit_sha=''):
    return True

"""
@ param  configuration parameters like user, repos and start_sha
@ return nothing 
@ callee deal_commit(gh, sha, writer)
@ caller fetch_hunk
@ involve fetch and analyze each commit and save hunk info with log
"""
def fetch_issue(commit_sha=''):

    # initiate Github with given user and repos
    gh = Github(login='993273596@qq.com', password='nx153156', user=my_constant.USER, repo=my_constant.REPOS)

    # initiate csvfile which store the commit info
    hunk_file = file(my_constant.FETCH_HUNK_FILE_NAME, 'wb')
    hunk_writer = csv.writer(hunk_file)
    hunk_writer.writerow(my_constant.FETCH_HUNK_TITLE)

    # fetch all the commits of given repos
    commits = gh.repos.commits.list(sha=commit_sha)
    total_file = 0
    total_cpp = 0
    total_log_cpp = 0
    for commit in commits.iterator():
        # call deal_commit function to deal with each commit
        deal_issue()

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

    commit_sha = ''
    # with function to retieve all the commits of given path
    fetch_issue(True, commit_sha)
    # deal with hunk
