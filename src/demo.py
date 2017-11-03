import my_constant
import analyze_control_old_new
import analyze_control_old_new_cluster
import analyze_control_repos
import analyze_control_clone
import statistics
import gumtree_api

def analyze_and_cluster_old_new(repos_list, repos_name_list):
    """
    @ param repos list, all the reposes you want to deal with\n
    @ return nothing \n
    @ involve call analyze old new and cluster for each repos\n
    """
    index = 0
    for repos in repos_list:
        print 'now analyzing repos %s' %repos
        # update repos value of my constant
        my_constant.reset_repos(repos)
        # analyze and cluster old and new
        analyze_control_old_new.analyze_old_new(False)
        analyze_control_old_new_cluster.cluster()
        analyze_control_old_new_cluster.generate_class()
        # analyze and cluster repos
        analyze_control_repos.analyze_repos(repos_name_list[index])
        analyze_control_repos.cluster_repos_log()
        analyze_control_clone.seek_clone()
        index += 1
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
        my_constant.reset_repos(repos)
        statistics.perform_statistic()

"""
main function
"""
if __name__ == "__main__":
    reposes = ['httpd', 'git', 'mutt', 'curl', 'rsync']
    repos_names = [ 'mutt-1.7.2','curl-7.41.0']
    do_statistics(reposes)


