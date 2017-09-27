ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00696)
                "cache: 'only-if-cached' requested and no cached entity, "
                "returning 504 Gateway Timeout for: %s", r->uri);