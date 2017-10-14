ap_log_rerror(
                APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(02464) "cache: Method '%s' not cacheable by mod_cache, ignoring: %s", r->method, r->uri);