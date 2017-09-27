            continue;
        }

        perform_idle_server_maintenance(pconf);
    }

    retained->mpm->mpm_state = AP_MPMQ_STOPPING;

    if (retained->mpm->shutdown_pending && retained->mpm->is_ungraceful) {
        /* Time to shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
        if (ap_unixd_killpg(getpgrp(), SIGTERM) < 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00168) "killpg SIGTERM");
        }
