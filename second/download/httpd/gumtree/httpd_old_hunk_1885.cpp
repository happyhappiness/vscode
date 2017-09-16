	    hold_off_on_exponential_spawning = 10;

	}



	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, server_conf,

		    "%s configured -- resuming normal operations",

		    ap_get_server_version());

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, server_conf,

		    "Server built: %s", ap_get_server_built());

	if (ap_suexec_enabled) {

	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, server_conf,

		         "suEXEC mechanism enabled (wrapper: %s)", SUEXEC_BIN);

	}

	restart_pending = shutdown_pending = 0;



	while (!restart_pending && !shutdown_pending) {

	    int child_slot;

	    ap_wait_t status;

	    int pid = wait_or_timeout(&status);

