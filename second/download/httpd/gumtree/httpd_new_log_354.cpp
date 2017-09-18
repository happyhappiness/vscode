ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                             r->server, "proxy (PID %d): readbytes: %#x",
                             getpid(), readbytes);