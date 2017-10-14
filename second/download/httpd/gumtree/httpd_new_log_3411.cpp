ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00781)
                "Incoming request is asking for a uncached version of "
                "%s, but we have been configured to ignore it and "
                "serve a cached response anyway",
                r->unparsed_uri);