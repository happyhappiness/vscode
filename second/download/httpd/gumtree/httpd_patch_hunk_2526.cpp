  *
  * After the various failure cases, the cache lock is proactively removed, so
  * that another request is given the opportunity to attempt to cache without
  * waiting for a potentially slow client to acknowledge the failure.
  */
 
-static int cache_save_filter(ap_filter_t *f, apr_bucket_brigade *in)
+static apr_status_t cache_save_filter(ap_filter_t *f, apr_bucket_brigade *in)
 {
     int rv = !OK;
     request_rec *r = f->r;
-    cache_request_rec *cache;
+    cache_request_rec *cache = (cache_request_rec *)f->ctx;
     cache_server_conf *conf;
-    const char *cc_out, *cl;
+    cache_dir_conf *dconf;
+    cache_control_t control;
+    const char *cc_out, *cl, *pragma;
     const char *exps, *lastmods, *dates, *etag;
     apr_time_t exp, date, lastmod, now;
     apr_off_t size = -1;
     cache_info *info = NULL;
     char *reason;
     apr_pool_t *p;
     apr_bucket *e;
+    apr_table_t *headers;
 
     conf = (cache_server_conf *) ap_get_module_config(r->server->module_config,
                                                       &cache_module);
 
     /* Setup cache_request_rec */
-    cache = (cache_request_rec *) ap_get_module_config(r->request_config,
-                                                       &cache_module);
     if (!cache) {
         /* user likely configured CACHE_SAVE manually; they should really use
          * mod_cache configuration to do that
          */
-        cache = apr_pcalloc(r->pool, sizeof(cache_request_rec));
-        ap_set_module_config(r->request_config, &cache_module, cache);
-        cache->size = -1;
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00767)
+                "CACHE/CACHE_SAVE filter enabled while caching is disabled, ignoring");
+        ap_remove_output_filter(f);
+        return ap_pass_brigade(f->next, in);
     }
 
     reason = NULL;
     p = r->pool;
     /*
      * Pass Data to Cache
