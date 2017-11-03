import my_constant
import commands
import analyze_control_old_new
import analyze_control_old_new_cluster
import statistics
import gumtree_api

def analyze_and_cluster(repos_list):
    """
    @ param repos list, all the reposes you want to deal with\n
    @ return nothing \n
    @ involve call analyze old new and cluster for each repos\n
    """
    for repos in repos_list:
        print 'now analyzing repos %s' %repos
        # update repos value of my constant
        my_constant.reset_repos(repos)
        analyze_control_old_new.analyze_old_new(False)
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
        my_constant.reset_repos(repos)
        statistics.perform_statistic()

"""
main function
"""
if __name__ == "__main__":
    reposes = ['httpd', 'git', 'mutt', 'rtorrent', 'curl', 'sqlite', 'rsync']
    do_statistics(reposes)


