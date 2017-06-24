#-*-coding: utf-8 -*-
"""
@ involve : constant definition
"""
USER = 'Kitware'
REPOS = 'CMake'
# USER = 'bftpd'
# REPOS = 'bftpd'

"""
file name
"""
LOG_CALL_FILE_NAME = 'data/fetch/' + REPOS + '_logging_statement.csv'
FUNC_SIMILAIRTY_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_func_similarity.csv'
FETCH_HUNK_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_hunk_fetch.csv'
FETCH_LOG_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_log_fetch.csv'
ANALYZE_OLD_NEW_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_old_new_analyze.csv'
ANALYZE_REPOS_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_analyze.csv'
ANALYZE_CLONE_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_seek_clone.csv'
STATISTICS_CLONE_NUM_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_clone_statistics.csv'
STATISTICS_OLD_NEW_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_old_new_statistics.csv'
CLUSTER_REPOS_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_cluster.csv'
REPOS_SIMILARITY_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_similarity.csv'
NODE_DICT_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_node_dict.csv'

"""
fetch hunk file title and index
"""
FETCH_HUNK_TITLE = ['hunk', 'flag', 'logs', 'old_hunk_loc', 'new_hunk_loc']
FETCH_HUNK_HUNK = FETCH_HUNK_TITLE.index('hunk')
FETCH_HUNK_FLAG = FETCH_HUNK_TITLE.index('flag')
FETCH_HUNK_LOGS = FETCH_HUNK_TITLE.index('logs')
FETCH_HUNK_OLD_HUNK_LOC = FETCH_HUNK_TITLE.index('old_hunk_loc')
FETCH_HUNK_NEW_HUNK_LOC = FETCH_HUNK_TITLE.index('new_hunk_loc')

"""
fetch log file title and index
"""
FETCH_LOG_TITLE = ['commit_sha', 'commit_message', 'file_name', 'change_type', \
                'log_statement', 'old_log_loc', 'old_store_name', 'new_log_loc', 'new_store_name']
FETCH_LOG_COMMIT_SHA = FETCH_LOG_TITLE.index('commit_sha')
FETCH_LOG_COMMIT_MESSAGE = FETCH_LOG_TITLE.index('commit_message')
FETCH_LOG_FILE = FETCH_LOG_TITLE.index('file_name')
FETCH_LOG_CHANGE_TYPE = FETCH_LOG_TITLE.index('change_type')
FETCH_LOG_LOG = FETCH_LOG_TITLE.index('log_statement')
FETCH_LOG_OLD_LOC = FETCH_LOG_TITLE.index('old_log_loc')
FETCH_LOG_OLD_FILE = FETCH_LOG_TITLE.index('old_store_name')
FETCH_LOG_NEW_LOC = FETCH_LOG_TITLE.index('new_log_loc')
FETCH_LOG_NEW_FILE = FETCH_LOG_TITLE.index('new_store_name')

"""
analyze old new title and index
"""
ANALYZE_OLD_NEW_TITLE = ['identity', 'old_block_file', 'old_block_location',\
        'old_block_condition_feature', 'old_block_statement_feature', 'old_block_vector',\
        'new_block_file', 'new_block_location', \
        'new_block_condition_feature', 'new_block_statement_feature', 'new_block_vector', \
        'commit_sha', 'commit_message', 'file_name', 'log_info']
ANALYZE_OLD_NEW_OLD_BLOCK_VECTOR = ANALYZE_OLD_NEW_TITLE.index('old_block_vector')
ANALYZE_OLD_NEW_NEW_BLOCK_VECTOR = ANALYZE_OLD_NEW_TITLE.index('new_block_vector')
ANALYZE_OLD_NEW_LOG_INFO = ANALYZE_OLD_NEW_TITLE.index('log_info')


"""
analyze repos / cluster repos title and index
"""
ANALYZE_REPOS_TITLE = ['identity', 'file', 'location', 'condition_feature',\
                                                         'statement_feature', 'vector']
CLUSTER_REPOS_TITLE = ['identity', 'file', 'location', 'condition_feature',\
                                        'statement_feature', 'vector', 'cluster_index']
ANALYZE_REPOS_VECTOR = ANALYZE_REPOS_TITLE.index('vector')

"""
analyze clone title
"""
ANALYZE_CLONE_TITLE = ['identity', 'old_block_file', 'old_block_location',\
        'old_block_condition_feature', 'old_block_statement_feature', 'old_block_vector',\
        'new_block_file', 'new_block_location', \
        'new_block_condition_feature', 'new_block_statement_feature', 'new_block_vector', \
        'commit_sha', 'commit_message', 'file_name', 'log_info', \
        \
        'identity', 'file', 'location', 'condition_feature', 'statement_feature', 'vector']

"""
flag type && log type
"""
FLAG_LOG_DELETE = -2
FLAG_DELETE = -1
FLAG_LOG_DELETE_CONTINUE = -3
FLAG_NO_CHANGE = 0
FLAG_ADD = 1
FLAG_LOG_ADD = 2
FLAG_LOG_ADD_CONTINUE = 3

LOG_ADD = 0
LOG_DELETE = 1
LOG_MOVE = 2
LOG_MODIFY = 3
LOG_COCHANGE = 4

"""
split string for statement to get tokens
"""
SPLIT_STR = r'[\W\s]'