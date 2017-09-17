ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "httpd: #perl SSI disallowed by IncludesNoExec in %s",
                    r->filename);