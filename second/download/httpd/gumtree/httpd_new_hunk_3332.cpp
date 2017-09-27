        /* Kill 'em all.  Since the child acts the same on the parents SIGTERM
         * and a SIGHUP, we may as well use the same signal, because some user
         * pthreads are stealing signals from us left and right.
         */
        ap_event_pod_killpg(pod, ap_daemons_limit, FALSE);

        ap_reclaim_child_processes(1,  /* Start with SIGTERM */
                                   event_note_child_killed);
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00494)
                     "SIGHUP received.  Attempting to restart");
    }

    return OK;
}

