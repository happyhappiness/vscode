

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, server_conf,

		    "%s configured -- resuming normal operations",

		    ap_get_server_version());

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, server_conf,

		    "Server built: %s", ap_get_server_built());

	restart_pending = shutdown_pending = 0;



	while (!restart_pending && !shutdown_pending) {

	    int child_slot;

	    int status;

	    int pid = wait_or_timeout(&status);



	    /* XXX: if it takes longer than 1 second for all our children

	     * to start up and get into IDLE state then we may spawn an

	     * extra child

	     */

