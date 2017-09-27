ap_log_error(APLOG_MARK, APLOG_WARNING, 0, f->r->server,
                 "cache: CACHE filter was added twice, or was added in quick "
    		     "handler mode and will be ignored.");