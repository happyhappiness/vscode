ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0, ap_server_conf,
		    AP_SIG_GRACEFUL_STRING " received.  Doing graceful restart");