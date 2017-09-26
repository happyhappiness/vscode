				"removed PID file %s (pid=%ld)",
				pidfile, (long)getpid());
	}

	ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
		    "caught SIGTERM, shutting down");
	return 1;
    }

    /* we've been told to restart */
    apr_signal(SIGHUP, SIG_IGN);
    if (one_process) {
	/* not worth thinking about */
	return 1;
    }

    /* advance to the next generation */
    /* XXX: we really need to make sure this new generation number isn't in
     * use by any of the children.
     */
    ++ap_my_generation;
    ap_scoreboard_image->global->running_generation = ap_my_generation;
    
    if (is_graceful) {
	ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
		    "Graceful restart requested, doing restart");

	/* kill off the idle ones */
        ap_mpm_pod_killpg(pod, ap_max_daemons_limit);

	/* This is mostly for debugging... so that we know what is still
	    * gracefully dealing with existing request.  This will break
	    * in a very nasty way if we ever have the scoreboard totally
	    * file-based (no shared memory)
	    */
	for (index = 0; index < ap_daemons_limit; ++index) {
	    if (ap_scoreboard_image->servers[index][0].status != SERVER_DEAD) {
		ap_scoreboard_image->servers[index][0].status = SERVER_GRACEFUL;
	    }
	}
    }
    else {
	/* Kill 'em off */
	if (unixd_killpg(getpgrp(), SIGHUP) < 0) {
