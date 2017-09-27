 
                 /* set aside the stale entry for accessing later */
                 cache->stale_headers = apr_table_copy(r->pool,
                         r->headers_in);
                 cache->stale_handle = h;
 
-                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00695)
-                        "Cached response for %s isn't fresh.  Adding/replacing "
-                        "conditional request headers.", r->uri);
+                /* if no existing conditionals, use conditionals of our own */
+                if (!mismatch) {
 
-                /* We can only revalidate with our own conditionals: remove the
-                 * conditions from the original request.
-                 */
-                apr_table_unset(r->headers_in, "If-Match");
-                apr_table_unset(r->headers_in, "If-Modified-Since");
-                apr_table_unset(r->headers_in, "If-None-Match");
-                apr_table_unset(r->headers_in, "If-Range");
-                apr_table_unset(r->headers_in, "If-Unmodified-Since");
-
-                etag = apr_table_get(h->resp_hdrs, "ETag");
-                lastmod = apr_table_get(h->resp_hdrs, "Last-Modified");
-
-                if (etag || lastmod) {
-                    /* If we have a cached etag and/or Last-Modified add in
-                     * our own conditionals.
-                     */
+                    ap_log_rerror(
+                            APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00695) "Cached response for %s isn't fresh. Adding "
+                            "conditional request headers.", r->uri);
+
+                    /* Remove existing conditionals that might conflict with ours */
+                    apr_table_unset(r->headers_in, "If-Match");
+                    apr_table_unset(r->headers_in, "If-Modified-Since");
+                    apr_table_unset(r->headers_in, "If-None-Match");
+                    apr_table_unset(r->headers_in, "If-Range");
+                    apr_table_unset(r->headers_in, "If-Unmodified-Since");
+
+                    etag = apr_table_get(h->resp_hdrs, "ETag");
+                    lastmod = apr_table_get(h->resp_hdrs, "Last-Modified");
+
+                    if (etag || lastmod) {
+                        /* If we have a cached etag and/or Last-Modified add in
+                         * our own conditionals.
+                         */
 
-                    if (etag) {
-                        apr_table_set(r->headers_in, "If-None-Match", etag);
-                    }
+                        if (etag) {
+                            apr_table_set(r->headers_in, "If-None-Match", etag);
+                        }
 
-                    if (lastmod) {
-                        apr_table_set(r->headers_in, "If-Modified-Since",
-                                lastmod);
-                    }
+                        if (lastmod) {
+                            apr_table_set(r->headers_in, "If-Modified-Since",
+                                    lastmod);
+                        }
 
-                    /*
-                     * Do not do Range requests with our own conditionals: If
-                     * we get 304 the Range does not matter and otherwise the
-                     * entity changed and we want to have the complete entity
-                     */
-                    apr_table_unset(r->headers_in, "Range");
+                        /*
+                         * Do not do Range requests with our own conditionals: If
+                         * we get 304 the Range does not matter and otherwise the
+                         * entity changed and we want to have the complete entity
+                         */
+                        apr_table_unset(r->headers_in, "Range");
+
+                    }
 
                 }
 
                 /* ready to revalidate, pretend we were never here */
                 return DECLINED;
             }
 
             /* Okay, this response looks okay.  Merge in our stuff and go. */
-            cache_accept_headers(h, r, 0);
+            cache_accept_headers(h, r, h->resp_hdrs, r->headers_out, 0);
 
             cache->handle = h;
             return OK;
         }
         case DECLINED: {
             /* try again with next cache type */
