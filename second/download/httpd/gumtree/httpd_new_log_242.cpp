ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR,
				    r, "Missing '}' on variable \"%s\"",
				    expansion);