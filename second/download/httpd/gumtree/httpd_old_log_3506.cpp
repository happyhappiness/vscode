ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "Cache lock obtained for stale cached URL, "
                     "revalidating entry: %s",
                     r->unparsed_uri);