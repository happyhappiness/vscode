ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                                 r->server,
                                 "cache: nonconditional - no cached "
                                 "etag/lastmods - add cache_in and DECLINE");