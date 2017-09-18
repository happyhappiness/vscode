     * use by any of the children.
     */
    ++ap_my_generation;
    ap_scoreboard_image->global->running_generation = ap_my_generation;
    
    if (is_graceful) {
	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0, ap_server_conf,
		    "Graceful restart requested, doing restart");

	/* kill off the idle ones */
        ap_mpm_pod_killpg(pod, ap_daemons_limit);

	/* This is mostly for debugging... so that we know what is still
