ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "Incoming request is asking for a uncached version of "
                     "%s, but we know better and are ignoring it",
                     r->unparsed_uri);