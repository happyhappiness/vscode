ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
			    "ISA sent invalid headers: %s", r->filename);