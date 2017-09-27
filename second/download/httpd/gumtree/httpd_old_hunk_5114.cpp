    ap_scoreboard_image->global->running_generation = retained->my_generation;

    if (retained->is_graceful) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00297)
                     AP_SIG_GRACEFUL_STRING " received.  Doing graceful restart");
        /* wake up the children...time to die.  But we'll have more soon */
        ap_worker_pod_killpg(pod, ap_daemons_limit, TRUE);


        /* This is mostly for debugging... so that we know what is still
         * gracefully dealing with existing request.
         */

    }
    else {
        /* Kill 'em all.  Since the child acts the same on the parents SIGTERM
         * and a SIGHUP, we may as well use the same signal, because some user
         * pthreads are stealing signals from us left and right.
         */
        ap_worker_pod_killpg(pod, ap_daemons_limit, FALSE);

        ap_reclaim_child_processes(1, /* Start with SIGTERM */
                                   worker_note_child_killed);
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00298)
                    "SIGHUP received.  Attempting to restart");
    }
