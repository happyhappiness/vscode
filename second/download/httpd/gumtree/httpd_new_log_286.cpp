ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		    "File does not exist: %s",
                    (r->path_info
                     ? ap_pstrcat(r->pool, r->filename, r->path_info, NULL)
                     : r->filename));