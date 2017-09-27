                  * the CACHE_SAVE filter at the precise location where
                  * the admin wants to cache the content. All filters that
                  * lie before and after the original location of the CACHE
                  * filter will remain in place.
                  */
                 if (cache_replace_filter(r->output_filters,
-                        cache_filter_handle, cache_save_handle)) {
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
-                            r->server, "Replacing CACHE with CACHE_SAVE "
+                        cache_filter_handle, cache_save_handle,
+                        ap_get_input_filter_handle("SUBREQ_CORE"))) {
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
+                            r, APLOGNO(00758) "Replacing CACHE with CACHE_SAVE "
                             "filter for %s", r->uri);
                 }
 
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
+                /* save away the save filter stack */
+                cache->save_filter = cache_get_filter(r->output_filters,
+                        cache_save_filter_handle);
+
+                apr_pool_userdata_setn(cache, CACHE_CTX_KEY, NULL, r->pool);
+
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00759)
                         "Adding CACHE_REMOVE_URL filter for %s",
                         r->uri);
 
                 /* Add cache_remove_url filter to this request to remove a
                  * stale cache entry if needed. Also put the current cache
                  * request rec in the filter context, as the request that
