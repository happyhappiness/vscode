ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r->server, 
                    "File does not exist: %s", 
		     r->path_info 
		         ? ap_pstrcat(r->pool, r->filename, r->path_info, NULL)
		         : r->filename);