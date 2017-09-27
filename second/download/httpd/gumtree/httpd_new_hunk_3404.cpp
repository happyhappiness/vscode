    /* *** We now do this was back in winnt_rewrite_args
     * pipe = GetStdHandle(STD_INPUT_HANDLE);
     */
    if (!ReadFile(pipe, &ready_event, sizeof(HANDLE),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(HANDLE))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00384)
                     "Child: Unable to retrieve the ready event from the parent");
        exit(APEXIT_CHILDINIT);
    }

    SetEvent(ready_event);
    CloseHandle(ready_event);

    if (!ReadFile(pipe, child_exit_event, sizeof(HANDLE),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(HANDLE))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00385)
                     "Child: Unable to retrieve the exit event from the parent");
        exit(APEXIT_CHILDINIT);
    }

    if (!ReadFile(pipe, &os_start, sizeof(os_start),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(os_start))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00386)
                     "Child: Unable to retrieve the start_mutex from the parent");
        exit(APEXIT_CHILDINIT);
    }
    *child_start_mutex = NULL;
    if ((rv = apr_os_proc_mutex_put(child_start_mutex, &os_start, s->process->pool))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00387)
                     "Child: Unable to access the start_mutex from the parent");
        exit(APEXIT_CHILDINIT);
    }

    if (!ReadFile(pipe, &hScore, sizeof(hScore),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(hScore))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00388)
                     "Child: Unable to retrieve the scoreboard from the parent");
        exit(APEXIT_CHILDINIT);
    }
    *scoreboard_shm = NULL;
    if ((rv = apr_os_shm_put(scoreboard_shm, &hScore, s->process->pool))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00389)
                     "Child: Unable to access the scoreboard from the parent");
        exit(APEXIT_CHILDINIT);
    }

    rv = ap_reopen_scoreboard(s->process->pool, scoreboard_shm, 1);
    if (rv || !(sb_shared = apr_shm_baseaddr_get(*scoreboard_shm))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00390)
                     "Child: Unable to reopen the scoreboard from the parent");
        exit(APEXIT_CHILDINIT);
    }
    /* We must 'initialize' the scoreboard to relink all the
     * process-local pointer arrays into the shared memory block.
     */
    ap_init_scoreboard(sb_shared);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00391)
                 "Child: Retrieved our scoreboard from the parent.");
}


static int send_handles_to_child(apr_pool_t *p,
                                 HANDLE child_ready_event,
                                 HANDLE child_exit_event,
