ap_log_error(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, 0, r->server,
                 "disk_cache: Caching headers for URL %s",  dobj->name);