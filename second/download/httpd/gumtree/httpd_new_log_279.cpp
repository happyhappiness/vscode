ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                            "variable must precede value in set directive in %s",
			    r->filename);