
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                "%s configured -- resuming normal operations",
                ap_get_server_description());
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
                "Server built: %s", ap_get_server_built());
#ifdef AP_MPM_WANT_SET_ACCEPT_LOCK_MECH
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                "AcceptMutex: %s (default: %s)",
                apr_proc_mutex_name(accept_mutex),
                apr_proc_mutex_defname());
#endif
    restart_pending = shutdown_pending = 0;

    mpm_state = AP_MPMQ_RUNNING;

    while (!restart_pending && !shutdown_pending) {
        int child_slot;
        apr_exit_why_e exitwhy;
        int status, processed_status;
        /* this is a memory leak, but I'll fix it later. */
        apr_proc_t pid;

        ap_wait_or_timeout(&exitwhy, &status, &pid, pconf);

        /* XXX: if it takes longer than 1 second for all our children
         * to start up and get into IDLE state then we may spawn an
         * extra child
         */
        if (pid.pid != -1) {
            processed_status = ap_process_child_status(&pid, exitwhy, status);
            if (processed_status == APEXIT_CHILDFATAL) {
                mpm_state = AP_MPMQ_STOPPING;
                return 1;
            }

            /* non-fatal death... note that it's gone in the scoreboard. */
            child_slot = find_child_by_pid(&pid);
            if (child_slot >= 0) {
                (void) ap_update_child_status_from_indexes(child_slot, 0, SERVER_DEAD,
                                                           (request_rec *) NULL);
                if (processed_status == APEXIT_CHILDSICK) {
                    /* child detected a resource shortage (E[NM]FILE, ENOBUFS, etc)
                     * cut the fork rate to the minimum
