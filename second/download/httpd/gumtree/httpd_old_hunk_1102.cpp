    
    if (is_graceful) {
	ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
		    "Graceful restart requested, doing restart");

	/* kill off the idle ones */
        ap_mpm_pod_killpg(pod, ap_daemons_limit);

	/* This is mostly for debugging... so that we know what is still
	    * gracefully dealing with existing request.  This will break
	    * in a very nasty way if we ever have the scoreboard totally
	    * file-based (no shared memory)
	    */
