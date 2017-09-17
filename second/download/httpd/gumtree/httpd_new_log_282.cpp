ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
			    "mod_include: error reading directive in %s",
			    r->filename);