     * use by any of the children.
     */
    ++ap_my_generation;
    ap_scoreboard_image->global->running_generation = ap_my_generation;
    
    if (is_graceful) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                     AP_SIG_GRACEFUL_STRING " received.  Doing graceful restart");
        /* wake up the children...time to die.  But we'll have more soon */
        ap_mpm_pod_killpg(pod, ap_daemons_limit);
    

        /* This is mostly for debugging... so that we know what is still
         * gracefully dealing with existing request.
         */
        
    }
    else {
        /* Kill 'em all.  Since the child acts the same on the parents SIGTERM 
         * and a SIGHUP, we may as well use the same signal, because some user
         * pthreads are stealing signals from us left and right.
         */
        ap_mpm_pod_killpg(pod, ap_daemons_limit);

        ap_reclaim_child_processes(1);                /* Start with SIGTERM */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                    "SIGHUP received.  Attempting to restart");
    }

    return 0;
}

