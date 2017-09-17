ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "Syntax error in type map --- no ':': %s", r->filename);