ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
                                 r->server, "proxy (PID %d): readbytes: %#x",
                                 getpid(), readbytes);