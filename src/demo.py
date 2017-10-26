import commands
import my_constant
import analyze_control_old_new
import analyze_control_old_new_cluster
import statistics
import gumtree_api

def reset_repos(repository):
    """
    @ param new repository\n
    @ return nothing \n
    @ involve reset my_constant repos variable and related variables\n
    """
    my_constant.REPOS = repository

    """
    stroed file name prefix
    """
    # parent
    my_constant.BASE_DIR = '/usr/info/code/cpp/LogMonitor/LogMonitor'
    my_constant.CURR_REPOS_DIR = my_constant.BASE_DIR + '/second/download/' + my_constant.REPOS + '/'
    # patch dir
    my_constant.PATCH_DIR = my_constant.CURR_REPOS_DIR + 'patch/'
    # repos
    my_constant.REPOS_DIR = my_constant.CURR_REPOS_DIR + 'repos/'
    # gumtree dir(hunk, block, function)
    my_constant.GUMTREE_DIR = my_constant.CURR_REPOS_DIR + 'gumtree/'
    # hunk
    my_constant.DOWNLOAD_PATCH_HUNK = my_constant.GUMTREE_DIR + my_constant.REPOS + '_patch_hunk_'
    my_constant.DOWNLOAD_OLD_HUNK = my_constant.GUMTREE_DIR + my_constant.REPOS + '_old_hunk_'
    my_constant.DOWNLOAD_NEW_HUNK = my_constant.GUMTREE_DIR + my_constant.REPOS + '_new_hunk_'
    # log
    my_constant.SAVE_OLD_LOG = my_constant.GUMTREE_DIR + my_constant.REPOS + '_old_log_'
    my_constant.SAVE_NEW_LOG = my_constant.GUMTREE_DIR + my_constant.REPOS + '_new_log_'
    # function
    my_constant.SAVE_FUNCTION = my_constant.GUMTREE_DIR + my_constant.REPOS + '_function_'

    """
    file name
    """
    my_constant.LOG_CALL_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_logging_statement.csv'
    my_constant.FUNC_SIMILAIRTY_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_func_similarity.csv'
    my_constant.FETCH_HUNK_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_hunk_fetch.csv'
    my_constant.FETCH_LOG_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_log_fetch.csv'
    my_constant.ANALYZE_OLD_NEW_GUMTREE_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_old_new_gumtree_analyze.csv'
    my_constant.ANALYZE_REPOS_LOG_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_repos_log_analyze.csv'
    my_constant.ANALYZE_REPOS_BASIC_BLOCK_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_repos_basic_block_analyze.csv'
    my_constant.ANALYZE_OLD_NEW_LLVM_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_old_new_llvm_analyze.csv'
    my_constant.ANALYZE_CLONE_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_seek_clone.csv'
    my_constant.STATISTICS_CLONE_NUM_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_clone_statistics.csv'
    my_constant.CLUSTER_FEATURE_OLD_NEW_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_old_new_cluster_feature.csv'
    my_constant.CLUSTER_EDITION_OLD_NEW_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_old_new_cluster_edition.csv'
    my_constant.CLUSTER_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_old_new_cluster_edition_and_feature.csv'
    my_constant.STATISTICS_OLD_NEW_TEMP_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_old_new_statistics_temp.csv'
    my_constant.CLUSTER_REPOS_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_repos_cluster.csv'
    my_constant.ANALYZE_REPOS_CLASS_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_repos_class.csv'
    my_constant.REPOS_SIMILARITY_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_repos_similarity.csv'
    my_constant.NODE_DICT_FILE_NAME = 'data/fetch/' + my_constant.REPOS + '_node_dict.csv'

def analyze_and_cluster(repos_list):
    """
    @ param repos list, all the reposes you want to deal with\n
    @ return nothing \n
    @ involve call analyze old new and cluster for each repos\n
    """
    for repos in repos_list:
        print 'now analyzing repos %s' %repos
        # update repos value of my constant
        reset_repos(repos)
        analyze_control_old_new.analyze_old_new(True)
        analyze_control_old_new_cluster.cluster()
    # close jvm
    gumtree_api.close_jvm()

def do_statistics(repos_list):
    """
    @ param repos list, all the reposes you want to deal with\n
    @ return nothing \n
    @ involve do statistics(type info, cluster info, cluster type info) for each repos\n
    """
    for repos in repos_list:
        print '\n****************now analyzing repos %s***************' %repos
        # update repos value of my constant
        reset_repos(repos)
        statistics.perform_statistic()

"""
main function
"""
if __name__ == "__main__":
    reposes = ['httpd', 'git', 'mutt', 'rtorrent', 'curl', 'sqlite', 'rsync']
    do_statistics(reposes)


