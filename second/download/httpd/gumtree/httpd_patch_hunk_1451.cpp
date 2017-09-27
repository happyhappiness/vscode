                     }
 
                     if (lastmod) {
                         apr_table_set(r->headers_in, "If-Modified-Since",
                                       lastmod);
                     }
-                    cache->stale_handle = h;
-                }
-                else {
-                    int irv;
-
                     /*
-                     * The copy isn't fresh enough, but we cannot revalidate.
-                     * So it is the same case as if there had not been a cached
-                     * entry at all. Thus delete the entry from cache.
+                     * Do not do Range requests with our own conditionals: If
+                     * we get 304 the Range does not matter and otherwise the
+                     * entity changed and we want to have the complete entity
                      */
-                    irv = cache->provider->remove_url(h, r->pool);
-                    if (irv != OK) {
-                        ap_log_error(APLOG_MARK, APLOG_DEBUG, irv, r->server,
-                                     "cache: attempt to remove url from cache unsuccessful.");
-                    }
+                    apr_table_unset(r->headers_in, "Range");
                 }
-
                 return DECLINED;
             }
 
             /* Okay, this response looks okay.  Merge in our stuff and go. */
             ap_cache_accept_headers(h, r, 0);
 
