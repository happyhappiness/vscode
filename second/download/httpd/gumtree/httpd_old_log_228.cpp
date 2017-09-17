ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		    "internal error in mod_cern_meta: %s", r->filename);