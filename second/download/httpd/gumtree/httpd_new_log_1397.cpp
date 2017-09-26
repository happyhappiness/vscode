ap_log_error(APLOG_MARK, APLOG_DEBUG, status, r->server,
                     "Attempt to obtain a cache lock for stale "
                     "cached URL failed, revalidating entry anyway: %s",
                     r->unparsed_uri);