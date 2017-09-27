ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
                  "Cached response for %s isn't fresh.  Adding/replacing "
                  "conditional request headers.", r->uri);