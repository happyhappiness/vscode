         ap_remove_output_filter(next);
         next = next->next;
     }
 
     /* kick off the filter stack */
     out = apr_brigade_create(r->pool, r->connection->bucket_alloc);
-    rv = ap_pass_brigade(r->output_filters, out);
-    if (rv != APR_SUCCESS) {
-        if (rv != AP_FILTER_ERROR) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
-                         "cache: error returned while trying to return %s "
-                         "cached data",
-                         cache->provider_name);
-        }
-        return rv;
-    }
-
-    return OK;
+    e = apr_bucket_eos_create(out->bucket_alloc);
+    APR_BRIGADE_INSERT_TAIL(out, e);
+    return ap_pass_brigade_fchk(r, out, "cache(%s): ap_pass_brigade returned",
+                                cache->provider_name);
 }
 
 /*
  * CACHE_OUT filter
  * ----------------
  *
  * Deliver cached content (headers and body) up the stack.
  */
-static int cache_out_filter(ap_filter_t *f, apr_bucket_brigade *bb)
+static apr_status_t cache_out_filter(ap_filter_t *f, apr_bucket_brigade *in)
 {
     request_rec *r = f->r;
-    cache_request_rec *cache;
-
-    cache = (cache_request_rec *) ap_get_module_config(r->request_config,
-                                                       &cache_module);
+    apr_bucket *e;
+    cache_request_rec *cache = (cache_request_rec *)f->ctx;
 
     if (!cache) {
         /* user likely configured CACHE_OUT manually; they should use mod_cache
          * configuration to do that */
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                     "CACHE_OUT enabled unexpectedly");
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00762)
+                "CACHE/CACHE_OUT filter enabled while caching is disabled, ignoring");
         ap_remove_output_filter(f);
-        return ap_pass_brigade(f->next, bb);
+        return ap_pass_brigade(f->next, in);
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
-                 "cache: running CACHE_OUT filter");
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00763)
+            "cache: running CACHE_OUT filter");
 
-    /* restore status of cached response */
-    /* XXX: This exposes a bug in mem_cache, since it does not
-     * restore the status into it's handle. */
-    r->status = cache->handle->cache_obj->info.status;
+    /* clean out any previous response up to EOS, if any */
+    for (e = APR_BRIGADE_FIRST(in);
+         e != APR_BRIGADE_SENTINEL(in);
+         e = APR_BUCKET_NEXT(e))
+    {
+        if (APR_BUCKET_IS_EOS(e)) {
+            apr_bucket_brigade *bb = apr_brigade_create(r->pool,
+                    r->connection->bucket_alloc);
 
-    /* recall_headers() was called in cache_select() */
-    cache->provider->recall_body(cache->handle, r->pool, bb);
+            /* restore status of cached response */
+            r->status = cache->handle->cache_obj->info.status;
 
-    /* This filter is done once it has served up its content */
-    ap_remove_output_filter(f);
+            /* recall_headers() was called in cache_select() */
+            cache->provider->recall_body(cache->handle, r->pool, bb);
+            APR_BRIGADE_PREPEND(in, bb);
+
+            /* This filter is done once it has served up its content */
+            ap_remove_output_filter(f);
+
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00764)
+                    "cache: serving %s", r->uri);
+            return ap_pass_brigade(f->next, in);
+
+        }
+        apr_bucket_delete(e);
+    }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
-                 "cache: serving %s", r->uri);
-    return ap_pass_brigade(f->next, bb);
+    return APR_SUCCESS;
+}
+
+/*
+ * Having jumped through all the hoops and decided to cache the
+ * response, call store_body() for each brigade, handling the
+ * case where the provider can't swallow the full brigade. In this
+ * case, we write the brigade we were passed out downstream, and
+ * loop around to try and cache some more until the in brigade is
+ * completely empty. As soon as the out brigade contains eos, call
+ * commit_entity() to finalise the cached element.
+ */
+static int cache_save_store(ap_filter_t *f, apr_bucket_brigade *in,
+        cache_server_conf *conf, cache_request_rec *cache)
+{
+    int rv = APR_SUCCESS;
+    apr_bucket *e;
+
+    /* pass the brigade in into the cache provider, which is then
+     * expected to move cached buckets to the out brigade, for us
+     * to pass up the filter stack. repeat until in is empty, or
+     * we fail.
+     */
+    while (APR_SUCCESS == rv && !APR_BRIGADE_EMPTY(in)) {
+
+        rv = cache->provider->store_body(cache->handle, f->r, in, cache->out);
+        if (rv != APR_SUCCESS) {
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, f->r, APLOGNO(00765)
+                    "cache: Cache provider's store_body failed!");
+            ap_remove_output_filter(f);
+
+            /* give someone else the chance to cache the file */
+            cache_remove_lock(conf, cache, f->r, NULL);
+
+            /* give up trying to cache, just step out the way */
+            APR_BRIGADE_PREPEND(in, cache->out);
+            return ap_pass_brigade(f->next, in);
+
+        }
+
+        /* does the out brigade contain eos? if so, we're done, commit! */
+        for (e = APR_BRIGADE_FIRST(cache->out);
+             e != APR_BRIGADE_SENTINEL(cache->out);
+             e = APR_BUCKET_NEXT(e))
+        {
+            if (APR_BUCKET_IS_EOS(e)) {
+                rv = cache->provider->commit_entity(cache->handle, f->r);
+                break;
+            }
+        }
+
+        /* conditionally remove the lock as soon as we see the eos bucket */
+        cache_remove_lock(conf, cache, f->r, cache->out);
+
+        if (APR_BRIGADE_EMPTY(cache->out)) {
+            if (APR_BRIGADE_EMPTY(in)) {
+                /* cache provider wants more data before passing the brigade
+                 * upstream, oblige the provider by leaving to fetch more.
+                 */
+                break;
+            }
+            else {
+                /* oops, no data out, but not all data read in either, be
+                 * safe and stand down to prevent a spin.
+                 */
+                ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, f->r, APLOGNO(00766)
+                        "cache: Cache provider's store_body returned an "
+                        "empty brigade, but didn't consume all of the"
+                        "input brigade, standing down to prevent a spin");
+                ap_remove_output_filter(f);
+
+                /* give someone else the chance to cache the file */
+                cache_remove_lock(conf, cache, f->r, NULL);
+
+                return ap_pass_brigade(f->next, in);
+            }
+        }
+
+        rv = ap_pass_brigade(f->next, cache->out);
+    }
+
+    return rv;
 }
 
 /*
  * CACHE_SAVE filter
  * ---------------
  *
