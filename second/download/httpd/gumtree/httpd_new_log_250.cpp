ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                    "httpd: #perl SSI disallowed by IncludesNoExec in %s",
                    r->filename);