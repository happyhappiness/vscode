         /* noop */
     }
     else if (exps != NULL && exp == APR_DATE_BAD) {
         /* if a broken Expires header is present, don't cache it */
         reason = apr_pstrcat(p, "Broken expires header: ", exps, NULL);
     }
-    else if (exp != APR_DATE_BAD && exp < r->request_time)
-    {
+    else if (!dconf->store_expired && exp != APR_DATE_BAD
+            && exp < r->request_time) {
         /* if a Expires header is in the past, don't cache it */
-        reason = "Expires header already expired, not cacheable";
+        reason = "Expires header already expired; not cacheable";
+    }
+    else if (!dconf->store_expired && (control.must_revalidate
+            || control.proxy_revalidate) && (!control.s_maxage_value
+            || (!control.s_maxage && !control.max_age_value)) && lastmods
+            == NULL && etag == NULL) {
+        /* if we're already stale, but can never revalidate, don't cache it */
+        reason
+                = "s-maxage or max-age zero and no Last-Modified or Etag; not cacheable";
     }
-    else if (!conf->ignorequerystring && r->parsed_uri.query && exps == NULL &&
-             !ap_cache_liststr(NULL, cc_out, "max-age", NULL) &&
-             !ap_cache_liststr(NULL, cc_out, "s-maxage", NULL)) {
+    else if (!conf->ignorequerystring && r->parsed_uri.query && exps == NULL
+            && !control.max_age && !control.s_maxage) {
         /* if a query string is present but no explicit expiration time,
          * don't cache it (RFC 2616/13.9 & 13.2.1)
          */
         reason = "Query string present but no explicit expiration time";
     }
     else if (r->status == HTTP_NOT_MODIFIED &&
              !cache->handle && !cache->stale_handle) {
         /* if the server said 304 Not Modified but we have no cache
          * file - pass this untouched to the user agent, it's not for us.
          */
         reason = "HTTP Status 304 Not Modified";
     }
-    else if (r->status == HTTP_OK && lastmods == NULL && etag == NULL
-             && (exps == NULL) && (conf->no_last_mod_ignore ==0) &&
-             !ap_cache_liststr(NULL, cc_out, "max-age", NULL) &&
-             !ap_cache_liststr(NULL, cc_out, "s-maxage", NULL)) {
+    else if (r->status == HTTP_OK && lastmods == NULL && etag == NULL && (exps
+            == NULL) && (dconf->no_last_mod_ignore == 0) && !control.max_age
+            && !control.s_maxage) {
         /* 200 OK response from HTTP/1.0 and up without Last-Modified,
          * Etag, Expires, Cache-Control:max-age, or Cache-Control:s-maxage
          * headers.
          */
         /* Note: mod-include clears last_modified/expires/etags - this
          * is why we have an optional function for a key-gen ;-)
          */
-        reason = "No Last-Modified, Etag, Expires, Cache-Control:max-age or Cache-Control:s-maxage headers";
-    }
-    else if (r->header_only && !cache->stale_handle) {
-        /* Forbid HEAD requests unless we have it cached already */
-        reason = "HTTP HEAD request";
+        reason = "No Last-Modified; Etag; Expires; Cache-Control:max-age or Cache-Control:s-maxage headers";
     }
-    else if (!conf->store_nostore &&
-             ap_cache_liststr(NULL, cc_out, "no-store", NULL)) {
+    else if (!dconf->store_nostore && control.no_store) {
         /* RFC2616 14.9.2 Cache-Control: no-store response
          * indicating do not cache, or stop now if you are
          * trying to cache it.
          */
-        /* FIXME: The Cache-Control: no-store could have come in on a 304,
-         * FIXME: while the original request wasn't conditional.  IOW, we
-         * FIXME:  made the the request conditional earlier to revalidate
-         * FIXME: our cached response.
-         */
         reason = "Cache-Control: no-store present";
     }
-    else if (!conf->store_private &&
-             ap_cache_liststr(NULL, cc_out, "private", NULL)) {
+    else if (!dconf->store_private && control.private) {
         /* RFC2616 14.9.1 Cache-Control: private response
          * this object is marked for this user's eyes only. Behave
          * as a tunnel.
          */
-        /* FIXME: See above (no-store) */
         reason = "Cache-Control: private present";
     }
-    else if (apr_table_get(r->headers_in, "Authorization") != NULL
-             && !(ap_cache_liststr(NULL, cc_out, "s-maxage", NULL)
-                  || ap_cache_liststr(NULL, cc_out, "must-revalidate", NULL)
-                  || ap_cache_liststr(NULL, cc_out, "public", NULL))) {
+    else if (apr_table_get(r->headers_in, "Authorization")
+            && !(control.s_maxage || control.must_revalidate
+                    || control.proxy_revalidate || control.public)) {
         /* RFC2616 14.8 Authorisation:
          * if authorisation is included in the request, we don't cache,
          * but we can cache if the following exceptions are true:
          * 1) If Cache-Control: s-maxage is included
          * 2) If Cache-Control: must-revalidate is included
          * 3) If Cache-Control: public is included
          */
         reason = "Authorization required";
     }
-    else if (ap_cache_liststr(NULL,
-                              apr_table_get(r->headers_out, "Vary"),
-                              "*", NULL)) {
+    else if (ap_find_token(NULL, apr_table_get(r->headers_out, "Vary"), "*")) {
         reason = "Vary header contains '*'";
     }
     else if (apr_table_get(r->subprocess_env, "no-cache") != NULL) {
         reason = "environment variable 'no-cache' is set";
     }
     else if (r->no_cache) {
         /* or we've been asked not to cache it above */
         reason = "r->no_cache present";
     }
 
+    /* Hold the phone. Some servers might allow us to cache a 2xx, but
+     * then make their 304 responses non cacheable. This leaves us in a
+     * sticky position. If the 304 is in answer to our own conditional
+     * request, we cannot send this 304 back to the client because the
+     * client isn't expecting it. Instead, our only option is to respect
+     * the answer to the question we asked (has it changed, answer was
+     * no) and return the cached item to the client, and then respect
+     * the uncacheable nature of this 304 by allowing the remove_url
+     * filter to kick in and remove the cached entity.
+     */
+    if (reason && r->status == HTTP_NOT_MODIFIED &&
+             cache->stale_handle) {
+        apr_bucket_brigade *bb;
+        apr_bucket *bkt;
+        int status;
+
+        cache->handle = cache->stale_handle;
+        info = &cache->handle->cache_obj->info;
+
+        /* Load in the saved status and clear the status line. */
+        r->status = info->status;
+        r->status_line = NULL;
+
+        bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
+
+        r->headers_in = cache->stale_headers;
+        status = ap_meets_conditions(r);
+        if (status != OK) {
+            r->status = status;
+
+            bkt = apr_bucket_flush_create(bb->bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(bb, bkt);
+        }
+        else {
+            /* RFC 2616 10.3.5 states that entity headers are not supposed
+             * to be in the 304 response.  Therefore, we need to combine the
+             * response headers with the cached headers *before* we update
+             * the cached headers.
+             *
+             * However, before doing that, we need to first merge in
+             * err_headers_out and we also need to strip any hop-by-hop
+             * headers that might have snuck in.
+             */
+            r->headers_out = ap_cache_cacheable_headers_out(r);
+
+            /* Merge in our cached headers.  However, keep any updated values. */
+            cache_accept_headers(cache->handle, r, 1);
+
+            cache->provider->recall_body(cache->handle, r->pool, bb);
+
+            bkt = apr_bucket_eos_create(bb->bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(bb, bkt);
+        }
+
+        cache->block_response = 1;
+
+        /* we've got a cache conditional hit! tell anyone who cares */
+        cache_run_cache_status(
+                cache->handle,
+                r,
+                r->headers_out,
+                AP_CACHE_REVALIDATE,
+                apr_psprintf(
+                        r->pool,
+                        "conditional cache hit: 304 was uncacheable though (%s); entity removed",
+                        reason));
+
+        /* let someone else attempt to cache */
+        cache_remove_lock(conf, cache, r, NULL);
+
+        return ap_pass_brigade(f->next, bb);
+    }
+
     if (reason) {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                     "cache: %s not cached. Reason: %s", r->unparsed_uri,
-                     reason);
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00768)
+                "cache: %s not cached. Reason: %s", r->unparsed_uri,
+                reason);
+
+        /* we've got a cache miss! tell anyone who cares */
+        cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_MISS,
+                reason);
 
         /* remove this filter from the chain */
         ap_remove_output_filter(f);
 
         /* remove the lock file unconditionally */
-        ap_cache_remove_lock(conf, r, cache->handle ?
-                (char *)cache->handle->cache_obj->key : NULL, NULL);
+        cache_remove_lock(conf, cache, r, NULL);
 
         /* ship the data up the stack */
         return ap_pass_brigade(f->next, in);
     }
 
     /* Make it so that we don't execute this path again. */
