             * yet, so we'd mistakenly create an extra server.
             */
            continue;
        }

        perform_idle_server_maintenance(pconf);
    }
    } /* one_process */

    mpm_state = AP_MPMQ_STOPPING;

    if (shutdown_pending && !is_graceful) {
        /* Time to shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
        if (ap_unixd_killpg(getpgrp(), SIGTERM) < 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "killpg SIGTERM");
        }
        ap_reclaim_child_processes(1);          /* Start with SIGTERM */

        /* cleanup pid file on normal shutdown */
        {
