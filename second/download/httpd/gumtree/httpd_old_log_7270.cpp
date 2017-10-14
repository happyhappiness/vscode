ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00698)
            "cache: Key for entity %s?%s is %s", r->uri,
            r->parsed_uri.query, *key);