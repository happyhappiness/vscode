ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "Cache already locked for stale cached URL, "
                     "pretend it is fresh: %s",
                     r->unparsed_uri);