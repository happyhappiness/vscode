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
@ param  github parameters gh and sha of commit and the counter for stored files and fileWriter
@ return file_count new counter of stored files 
@ callee deal_patch( sha, file, writer)
@ caller fetch_commit(user, repos, commit_sha='') ..
@ involve deal with commit and involved changed file
"""
def deal_commit(gh, sha):

    # retrieve info of commit with given sha
    commit = gh.repos.commits.get(sha=sha)
    message = commit.commit.message

    # save commit patch according to files
    for changed_file in commit.files:

        # filter to just deal with cpp and c files
        is_cpp = re.search('(.cpp|.c)$', changed_file.filename, re.I)
        # filter to not deal with test module files
        is_test_cpp = re.search('(test.cpp|.c)$', changed_file.filename, re.I)
        if is_cpp and not is_test_cpp:

            # download the blob of file
            source = gh.git_data.blobs.get(changed_file.sha).content
            # decode to retrieve the source file
            source = base64.b64decode(source)

            # store new file
            new_store_name = 'past_code/' + user + '_' + repos + '_new.cpp'
            temp_file = open(new_store_name, 'wb')
            temp_file.write(source)
            temp_file.close()

            # store patch file
            patch_store_name = 'past_code/' + user + '_' + repos + '_patch.cpp'
            temp_file = open(patch_store_name, 'wb')
            temp_file.write(changed_file.patch)
            temp_file.close()

            # compute old file with patch cmd
            old_store_name = 'past_code/' + user + '_' + repos + '_old.cpp'
            output = commands.getoutput('patch -R ' + new_store_name \
                      + ' -i ' + patch_store_name + ' -o ' + old_store_name)
            print output
            output = commands.getoutput('rm ' + patch_store_name)
            print output

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
    deal_commit(gh, commit_sha)


"""
main function
"""

# several configuration constant: user, repos
user = 'opencv'
repos = 'opencv'

commit_sha = '3fbe1f8d649ee709858b593bd69a4a85fe3224cb'

# with function to retieve all the commits of given path
fetch_commit(user, repos, commit_sha)

