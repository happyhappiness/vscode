     * use by any of the children.
     */
    ++ap_my_generation;
    ap_scoreboard_image->global->running_generation = ap_my_generation;
    
    if (is_graceful) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0, ap_server_conf,
                     AP_SIG_GRACEFUL_STRING " received.  Doing graceful restart");
        /* wake up the children...time to die.  But we'll have more soon */
        ap_mpm_pod_killpg(pod, ap_daemons_limit, TRUE);
    

        /* This is mostly for debugging... so that we know what is still
