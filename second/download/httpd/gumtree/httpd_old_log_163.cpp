ap_log_error(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, 0, r->server,
                     "disk_cache: Cached body for URL %s",  dobj->name);