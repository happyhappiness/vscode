    else

	dirconf = current_conn->server->lookup_defaults;

    if (!current_conn->keptalive) {

	if (sig == SIGPIPE) {

	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO,

			current_conn->server,

			"%s client stopped connection before %s completed",

			ap_get_remote_host(current_conn, dirconf, REMOTE_NAME),

			timeout_name ? timeout_name : "request");

	}

	else {

	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO,

			current_conn->server,

			"%s timed out for %s",

			timeout_name ? timeout_name : "request",

			ap_get_remote_host(current_conn, dirconf, REMOTE_NAME));

	}

    }



    if (timeout_req) {

	/* Someone has asked for this transaction to just be aborted

	 * if it times out...

