    else
	dirconf = current_conn->server->lookup_defaults;
    if (!current_conn->keptalive) {
	if (sig == SIGPIPE) {
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO,
			current_conn->server,
			"(client %s) stopped connection before %s completed",
			current_conn->remote_ip,
			timeout_name ? timeout_name : "request");
	}
	else {
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO,
			current_conn->server,
			"(client %s) %s timed out",
			current_conn->remote_ip,
			timeout_name ? timeout_name : "request");
	}
    }

    if (timeout_req) {
	/* Someone has asked for this transaction to just be aborted
	 * if it times out...
