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
@ param  configuration parameters like user, repos and start_sha
@ return nothing 
@ callee deal_commit(gh, sha, writer)
@ caller main ..
@ involve save commit info of given repos
"""
def fetch_commit(user, repos, commit_sha=''):
    
    # initiate Github with given user and repos 
    gh = Github(login='993273596@qq.com', password='xx', user=user, repo=repos)

    # fetch all the commits of given repos
    commits = gh.repos.commits.list()
    file_count = 1
    for commit in commits.iterator(): 
        print "now fetch no %d commit, commit sha is %s \n" %(file_count, commit.sha)
        file_count = file_count + 1

"""
main function
"""

# several configuration constant: user, repos
# user = 'mongodb'
# repos = 'mongo'
# user = 'opencv'
# repos = 'opencv'
user = 'apple'
repos = 'swift'

commit_sha = '1837918569e3c2d3d3f29329360449fa20ab75ef'

# with function to retieve all the commits of given path
fetch_commit(user, repos, commit_sha)

"""
follow time order or start from certain sha and then follow time order
"""
