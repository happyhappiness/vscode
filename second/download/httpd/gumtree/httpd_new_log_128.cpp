ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
		          "Failed to query lock-null status for %s",
			  r->filename);