ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO,
			current_conn->server,
			"%s timed out for %s",
			timeout_name ? timeout_name : "request",
			ap_get_remote_host(current_conn, dirconf, REMOTE_NAME));