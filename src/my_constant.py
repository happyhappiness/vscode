#-*-coding: utf-8 -*-
"""
@ involve : constant definition
"""
# USER = 'Kitware'
# REPOS = 'CMake'
USER = 'bftpd'
REPOS = 'bftpd'

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

FETCH_HUNK_TITLE = ['hunk', 'flag', 'logs', 'old_hunk_loc', 'new_hunk_loc']
FETCH_HUNK_HUNK = FETCH_HUNK_TITLE.index('hunk')
FETCH_HUNK_FLAG = FETCH_HUNK_TITLE.index('flag')
FETCH_HUNK_LOGS = FETCH_HUNK_TITLE.index('logs')
FETCH_HUNK_OLD_HUNK_LOC = FETCH_HUNK_TITLE.index('old_hunk_loc')
FETCH_HUNK_NEW_HUNK_LOC = FETCH_HUNK_TITLE.index('new_hunk_loc')

FETCH_LOG_TITLE = ['commit_sha', 'commit_message', 'file_name', 'change_type', \
                'log_statement', 'old_log_loc', 'old_store_name', 'new_log_loc', 'new_store_name']
FETCH_LOG_CHANGE_TYPE = FETCH_LOG_TITLE.index('change_type')
FETCH_LOG_LOG = FETCH_LOG_TITLE.index('log_statement')
FETCH_LOG_OLD_LOC = FETCH_LOG_TITLE.index('old_log_loc')
FETCH_LOG_OLD_FILE = FETCH_LOG_TITLE.index('old_store_name')
FETCH_LOG_NEW_LOC = FETCH_LOG_TITLE.index('new_log_loc')
FETCH_LOG_NEW_FILE = FETCH_LOG_TITLE.index('new_store_name')

ANALYZE_OLD_NEW_TITLE = ['commit_sha', 'commit_message', 'file_name', \
        'change_type', 'log_node', \
        'old_log_loc', 'old_store_name', 'new_log_loc', 'new_store_name', \
        'old_context_list', 'new_context_list', 'old_ddg_list', 'old_static_list', \
        'new_ddg_list', 'new_static_list']
ANALYZE_OLD_NEW_OLD_CONTEXT = ANALYZE_OLD_NEW_TITLE.index('old_context_list')
ANALYZE_OLD_NEW_OLD_DDG = ANALYZE_OLD_NEW_TITLE.index('old_ddg_list')
ANALYZE_OLD_NEW_NEW_CONTEXT = ANALYZE_OLD_NEW_TITLE.index('new_context_list')
ANALYZE_OLD_NEW_NEW_DDG = ANALYZE_OLD_NEW_TITLE.index('new_ddg_list')

ANALYZE_REPOS_TITLE = ['code', 'location', 'file', 'context_list', 'ddg_list', 'static_list']
CLUSTER_REPOS_TITLE = ['code', 'location', 'file', 'context_list', 'ddg_list', \
                                                                'static_list', 'cluster_index']
ANALYZE_REPOS_CONTEXT = ANALYZE_REPOS_TITLE.index('context_list')
ANALYZE_REPOS_DDG = ANALYZE_REPOS_TITLE.index('ddg_list')

ANALYZE_CLONE_TITLE = ['commit_sha', 'commit_message', 'file_name',\
        'change_type', 'log_node', \
        'old_log_loc', 'old_store_name', 'new_log_loc', 'new_store_name', \
        'old_context_list', 'new_context_list', 'old_ddg_list', 'old_static_list', \
        'new_ddg_list', 'new_static_list', \
        'clone_log', 'clone_location', 'clone_file_name', 'clone_context_list',\
        'clone_ddg_list', 'clone_static_list']

FLAG_LOG_DELETE = -2
FLAG_DELETE = -1
FLAG_NO_CHANGE = 0
FLAG_ADD = 1
FLAG_LOG_ADD = 2

LOG_ADD = 0
LOG_DELETE = 1
LOG_MOVE = 2
LOG_MODIFY = 3
