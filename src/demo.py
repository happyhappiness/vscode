import my_constant
import fetch_hunk
import analyze_hunk
import analyze_control_old_new
import analyze_control_old_new_cluster
import analyze_control_clone
import statistics
import gumtree_api

def regenerate_hunk(repos_list):
    """
    @ param repos list\n
    @ return nothing \n
    @ involve re-generate hunk and analyze hunk\n
    """
    for repos in repos_list:
        print 'now analyzing repos %s' %repos
        # update repos value of my constant
        my_constant.reset_repos(repos)
        # first -> refetch and reanalyze hunk
        fetch_hunk.fetch_version_diff(False)
        analyze_hunk.fetch_hunk()
    gumtree_api.close_jvm()

def regenerate_rule(reanalyze_gumtree=False):
    """
    @ param true if gumtree api update\n
    @ return nothing \n
    @ involve call analyze old new and cluster to generate rule(srcml update)\n
    """
    analyze_control_old_new.analyze_old_new(reanalyze_gumtree)
    analyze_control_old_new_cluster.cluster()
    analyze_control_old_new_cluster.generate_class()

def seek_clone_for_given_repos(repos_list, repos_name_list, reanalyze_rule=False, reanalyze_repos=False, reanalyze_gumtree=False):
    """
    @ param repos list, all the reposes you want to deal with, true if srcml api update, true if gumtree api update\n
    @ return nothing \n
    @ involve call analyze old new and cluster for each repos\n
    """
    index = 0
    for repos in repos_list:
        print 'now analyzing repos %s' %repos
        # update repos value of my constant
        my_constant.reset_repos(repos)
        if reanalyze_rule:
            regenerate_rule(reanalyze_gumtree)
        # seek clone
        analyze_control_clone.seek_clone(repos_name_list[index], reanalyze_repos, '')
        index += 1

def seek_clone_for_lastest_repos(repos_list, reanalyze_rule=False, reanalyze_repos=False, reanalyze_gumtree=False):
    """
    @ param repos list, true if srcml api update, true if gumtree api update\n
    @ return nothing \n
    @ involve for each repos, do: seek clone for all rules against lastest repos\n
    """
    for repos in repos_list:
        print 'now analyzing repos %s' %repos
        # update repos value of my constant
        my_constant.reset_repos(repos)
        if reanalyze_rule:
            regenerate_rule(reanalyze_gumtree)
        # seek clone
        analyze_control_clone.seek_clone_for_lastest_repos(reanalyze_repos)

    # close jvm
    if reanalyze_rule:
        gumtree_api.close_jvm()

def seek_clone_for_corresponding_repos(repos_list, reanalyze_rule=False, reanalyze_repos=False, reanalyze_gumtree=False):
    """
    @ param repos list, true if srcml api update, true if gumtree api update\n
    @ return nothing \n
    @ involve for each repos, do: seek clone for all rules against corresponding repos(which rule generate from)\n
    """
    for repos in repos_list:
        print 'now analyzing repos %s' %repos
        # update repos value of my constant
        my_constant.reset_repos(repos)
        if reanalyze_rule:
            regenerate_rule(reanalyze_gumtree)
        # seek clone
        analyze_control_clone.seek_clone_for_corresponding_repos(reanalyze_repos)
    # close jvm
    if reanalyze_rule:
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
        my_constant.reset_repos(repos)
        statistics.perform_statistic()

def perform_series(repos_list):
    """
    @ param repos list\n
    @ return nothing \n
    @ involve do everything for this repos\n
    """
    for repos in repos_list:
        print '\n****************now analyzing repos %s***************' %repos
        # analyze hunk
        fetch_hunk.fetch_version_diff(True)
        analyze_hunk.fetch_hunk()
        # analyze gumtree and srcml
        analyze_control_old_new.analyze_old_new(True)
        # generate rule
        analyze_control_old_new_cluster.cluster()
        analyze_control_old_new_cluster.generate_class()
        statistics.perform_statistic('data/evaluate/series.txt')
        # apply rule
        analyze_control_clone.seek_clone_for_corresponding_repos()
        analyze_control_clone.seek_clone_for_lastest_repos()

"""
main function
"""
if __name__ == "__main__":
    # 'httpd', 'git',
    reposes = ['httpd', 'git', 'mutt', 'curl', 'rsync', 'collectd']
    repos_names = ['httpd-2.3.8', 'git-2.6.7', 'mutt-1.7.2', 'curl-7.41.0', 'rsync-1.4.4']
    # seek_clone_for_given_repos(reposes, repos_names)
    # seek_clone_for_corresponding_repos(reposes[0:1], True, False, False)
    # seek_clone_for_corresponding_repos(reposes, False, False, False)
    # seek_clone_for_corresponding_repos(reposes[0:1], True, False, False)    
    # seek_clone_for_corresponding_repos(reposes[0:1], False, True, False)
    # seek_clone_for_corresponding_repos(reposes, False, False, True)
    # seek_clone_for_lastest_repos(reposes, False, False, False)
    repos_name = 'collectd'
    # perform_series([repos_name])
    do_statistics([repos_name])
    # regenerate_hunk(reposes)
    # do_statistics(reposes)


