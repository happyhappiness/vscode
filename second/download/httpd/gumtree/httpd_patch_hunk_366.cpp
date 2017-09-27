     if (f->r->status == HTTP_NOT_MODIFIED) {
         /* replace ourselves with CACHE_OUT filter */
         ap_add_output_filter_handle(cache_out_filter_handle, NULL,
                                     f->r, f->r->connection);
     }
     else {
-        /* replace ourselves with CACHE_IN filter */
-        ap_add_output_filter_handle(cache_in_filter_handle, NULL,
+        /* replace ourselves with CACHE_SAVE filter */
+        ap_add_output_filter_handle(cache_save_filter_handle, NULL,
                                     f->r, f->r->connection);
     }
     ap_remove_output_filter(f);
 
     return ap_pass_brigade(f->next, in);
 }
 
 
 /*
- * CACHE_IN filter
+ * CACHE_SAVE filter
  * ---------------
  *
  * Decide whether or not this content should be cached.
  * If we decide no it should:
  *   remove the filter from the chain
  * If we decide yes it should:
  *   pass the data to the storage manager
  *   pass the data to the next filter (the network)
  *
  */
 
-static int cache_in_filter(ap_filter_t *f, apr_bucket_brigade *in)
+static int cache_save_filter(ap_filter_t *f, apr_bucket_brigade *in)
 {
     int rv;
     int date_in_errhdr = 0;
     request_rec *r = f->r;
     cache_request_rec *cache;
     cache_server_conf *conf;
     char *url = r->unparsed_uri;
-    const char *cc_out, *cl;
+    const char *cc_in, *cc_out, *cl;
     const char *exps, *lastmods, *dates, *etag;
     apr_time_t exp, date, lastmod, now;
     apr_off_t size;
     cache_info *info;
     char *reason;
     apr_pool_t *p;
 
     /* check first whether running this filter has any point or not */
-    if(r->no_cache) {
+    /* If the user has Cache-Control: no-store from RFC 2616, don't store! */
+    cc_in = apr_table_get(r->headers_in, "Cache-Control");
+    if (r->no_cache || ap_cache_liststr(NULL, cc_in, "no-store", NULL)) {
         ap_remove_output_filter(f);
         return ap_pass_brigade(f->next, in);
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                 "cache: running CACHE_IN filter");
-
     /* Setup cache_request_rec */
-    cache = (cache_request_rec *) ap_get_module_config(r->request_config, &cache_module);
+    cache = (cache_request_rec *) ap_get_module_config(r->request_config,
+                                                       &cache_module);
     if (!cache) {
+        /* user likely configured CACHE_SAVE manually; they should really use
+         * mod_cache configuration to do that
+         */
         cache = apr_pcalloc(r->pool, sizeof(cache_request_rec));
         ap_set_module_config(r->request_config, &cache_module, cache);
     }
 
     reason = NULL;
     p = r->pool;
