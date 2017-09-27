ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00695)
                        "Cached response for %s isn't fresh.  Adding/replacing "
                        "conditional request headers.", r->uri);