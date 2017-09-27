ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                            r->server, "Replacing CACHE with CACHE_SAVE "
                            "filter for %s", r->uri);