    else {
	/* give the system some time to recover before kicking into
	    * exponential mode */
	hold_off_on_exponential_spawning = 10;
    }

    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0, ap_server_conf,
		"%s configured -- resuming normal operations",
		ap_get_server_version());
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, ap_server_conf,
		"Server built: %s", ap_get_server_built());
#ifdef AP_MPM_WANT_SET_ACCEPT_LOCK_MECH
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_DEBUG, 0, ap_server_conf,
		"AcceptMutex: %s", ap_valid_accept_mutex_string);
#endif
    restart_pending = shutdown_pending = 0;

    while (!restart_pending && !shutdown_pending) {
	int child_slot;
        apr_exit_why_e exitwhy;
