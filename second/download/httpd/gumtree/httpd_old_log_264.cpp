ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                            "Unmatched ')' in \"%s\" in file %s",
			    expr, r->filename);