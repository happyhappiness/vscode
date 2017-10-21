import commands
import my_constant
import analyze_control_old_new
import analyze_control_old_new_cluster

if __name__  == "__main__":
    reposes = ['httpd', 'git', 'mutt', 'rtorrent', 'curl', 'sqlite', 'rsync']
    for repos in reposes:
        my_constant.REPOS = repos
        analyze_control_old_new.analyze_old_new(True)
        analyze_control_old_new_cluster.cluster()
