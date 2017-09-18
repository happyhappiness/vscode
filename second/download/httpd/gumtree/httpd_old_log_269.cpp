ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, APR_EINVAL, r,
		    MODNAME ": request config should not be NULL");