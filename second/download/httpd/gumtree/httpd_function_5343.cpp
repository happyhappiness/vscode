static void accept_mutex_error(const char *func, apr_status_t rv, int process_slot)
{
    int level = APLOG_EMERG;

    if (ap_scoreboard_image->parent[process_slot].generation !=
        ap_scoreboard_image->global->running_generation) {
        level = APLOG_DEBUG; /* common to get these at restart time */
    } 
    else if (requests_this_child == INT_MAX  
        || ((requests_this_child == ap_max_requests_per_child)
            && ap_max_requests_per_child)) { 
        ap_log_error(APLOG_MARK, level, rv, ap_server_conf,
                     "apr_proc_mutex_%s failed "
                     "before this child process served any requests.",
                     func);
        clean_child_exit(APEXIT_CHILDSICK); 
    }
    ap_log_error(APLOG_MARK, level, rv, ap_server_conf,
                 "apr_proc_mutex_%s failed. Attempting to "
                 "shutdown process gracefully.", func);
    signal_threads(ST_GRACEFUL);
}