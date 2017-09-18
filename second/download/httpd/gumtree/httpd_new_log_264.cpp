ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
		    "internal error in mod_cern_meta: %s", r->filename);