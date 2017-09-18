ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                         "cache: no cache - add cache_in filter and DECLINE");