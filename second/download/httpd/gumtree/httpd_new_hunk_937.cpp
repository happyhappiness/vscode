        || (BytesRead != sizeof(hScore))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Child %d: Unable to retrieve the scoreboard from the parent", my_pid);
        exit(APEXIT_CHILDINIT);
    }
    *scoreboard_shm = NULL;
    if ((rv = apr_os_shm_put(scoreboard_shm, &hScore, s->process->pool))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                     "Child %d: Unable to access the scoreboard from the parent", my_pid);
        exit(APEXIT_CHILDINIT);
    }

    rv = ap_reopen_scoreboard(s->process->pool, scoreboard_shm, 1);
    if (rv || !(sb_shared = apr_shm_baseaddr_get(*scoreboard_shm))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "Child %d: Unable to reopen the scoreboard from the parent", my_pid);
        exit(APEXIT_CHILDINIT);
    }
    /* We must 'initialize' the scoreboard to relink all the
     * process-local pointer arrays into the shared memory block.
     */
