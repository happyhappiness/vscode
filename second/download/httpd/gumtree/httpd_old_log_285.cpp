ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, 0, r,
		      MODNAME ": invalid file type %d.", r->finfo.filetype);