ap_log_error(APLOG_MARK, APLOG_DEBUG, rv,
                             r->server, "Cache locked for url, not caching "
                             "response: %s", r->uri);