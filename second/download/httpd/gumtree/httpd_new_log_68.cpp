ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO,
			current_conn->server,
			"(client %s) stopped connection before %s completed",
			current_conn->remote_ip,
			timeout_name ? timeout_name : "request");