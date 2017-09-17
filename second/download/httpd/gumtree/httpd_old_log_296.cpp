ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r->server,
		    MODNAME ": invalid mode 0%o.", (unsigned int)r->finfo.st_mode);