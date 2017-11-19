static int send_handles_to_child(apr_pool_t *p,
                                 HANDLE child_ready_event,
                                 HANDLE child_exit_event,
                                 apr_proc_mutex_t *child_start_mutex,
                                 apr_shm_t *scoreboard_shm,
                                 HANDLE hProcess,
                                 apr_file_t *child_in)
{
    apr_status_t rv;
    HANDLE hCurrentProcess = GetCurrentProcess();
    HANDLE hDup;
    HANDLE os_start;
    HANDLE hScore;
    apr_size_t BytesWritten;

    if (!DuplicateHandle(hCurrentProcess, child_ready_event, hProcess, &hDup,
        EVENT_MODIFY_STATE | SYNCHRONIZE, FALSE, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00392)
                     "Parent: Unable to duplicate the ready event handle for the child");
        return -1;
    }
    if ((rv = apr_file_write_full(child_in, &hDup, sizeof(hDup), &BytesWritten))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00393)
                     "Parent: Unable to send the exit event handle to the child");
        return -1;
    }
    if (!DuplicateHandle(hCurrentProcess, child_exit_event, hProcess, &hDup,
                         EVENT_MODIFY_STATE | SYNCHRONIZE, FALSE, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00394)
                     "Parent: Unable to duplicate the exit event handle for the child");
        return -1;
    }
    if ((rv = apr_file_write_full(child_in, &hDup, sizeof(hDup), &BytesWritten))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00395)
                     "Parent: Unable to send the exit event handle to the child");
        return -1;
    }
    if ((rv = apr_os_proc_mutex_get(&os_start, child_start_mutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00396)
                     "Parent: Unable to retrieve the start mutex for the child");
        return -1;
    }
    if (!DuplicateHandle(hCurrentProcess, os_start, hProcess, &hDup,
                         SYNCHRONIZE, FALSE, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00397)
                     "Parent: Unable to duplicate the start mutex to the child");
        return -1;
    }
    if ((rv = apr_file_write_full(child_in, &hDup, sizeof(hDup), &BytesWritten))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00398)
                     "Parent: Unable to send the start mutex to the child");
        return -1;
    }
    if ((rv = apr_os_shm_get(&hScore, scoreboard_shm)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00399)
                     "Parent: Unable to retrieve the scoreboard handle for the child");
        return -1;
    }
    if (!DuplicateHandle(hCurrentProcess, hScore, hProcess, &hDup,
                         FILE_MAP_READ | FILE_MAP_WRITE, FALSE, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00400)
                     "Parent: Unable to duplicate the scoreboard handle to the child");
        return -1;
    }
    if ((rv = apr_file_write_full(child_in, &hDup, sizeof(hDup), &BytesWritten))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00401)
                     "Parent: Unable to send the scoreboard handle to the child");
        return -1;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00402)
                 "Parent: Sent the scoreboard to the child");
    return 0;
}