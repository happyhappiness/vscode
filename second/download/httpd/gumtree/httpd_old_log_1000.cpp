ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, NULL,
                    "Access to file %s denied by server: not a regular file",
                    name);