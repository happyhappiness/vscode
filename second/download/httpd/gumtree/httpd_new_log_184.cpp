ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
		     "ap_bgets() - proxy receive - Error reading from remote server %s",
		     proxyhost ? proxyhost : desthost);