ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r,
		    MODNAME ": invalid mode 0%o.", (unsigned int)r->finfo.st_mode);