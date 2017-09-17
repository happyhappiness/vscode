ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                            "variable must precede value in set directive in %s",
			    r->filename);