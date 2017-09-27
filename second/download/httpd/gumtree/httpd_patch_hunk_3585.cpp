 
                 }
                 else {
                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv,
                             r, APLOGNO(00752) "Cache locked for url, not caching "
                             "response: %s", r->uri);
+                    /* cache_select() may have added conditional headers */
+                    if (cache->stale_headers) {
+                        r->headers_in = cache->stale_headers;
+                    }
+
                 }
             }
             else {
                 if (cache->stale_headers) {
                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                             r, APLOGNO(00753) "Restoring request headers for %s",
