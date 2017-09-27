        perform_idle_server_maintenance(pconf);
    }
    } /* one_process */

    mpm_state = AP_MPMQ_STOPPING;

    if (shutdown_pending && !retained->is_graceful) {
        /* Time to shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
        if (ap_unixd_killpg(getpgrp(), SIGTERM) < 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00168) "killpg SIGTERM");
        }
        ap_reclaim_child_processes(1, /* Start with SIGTERM */
                                   prefork_note_child_killed);

        /* cleanup pid file on normal shutdown */
        ap_remove_pid(pconf, ap_pid_fname);
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00169)
                    "caught SIGTERM, shutting down");

        return DONE;
    } else if (shutdown_pending) {
        /* Time to perform a graceful shut down:
         * Reap the inactive children, and ask the active ones
