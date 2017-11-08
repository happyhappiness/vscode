int reap_children(int *exitcode, apr_exit_why_e *status)
{
    int n, pid;

    for (n = 0; n < ap_max_daemons_limit; ++n) {
        if (ap_scoreboard_image->servers[n][0].status != SERVER_DEAD &&
                kill((pid = ap_scoreboard_image->parent[n].pid), 0) == -1) {
            ap_update_child_status_from_indexes(n, 0, SERVER_DEAD, NULL);
            /* just mark it as having a successful exit status */
            *status = APR_PROC_EXIT;
            *exitcode = 0;
            return(pid);
        }
    }
    return 0;
}