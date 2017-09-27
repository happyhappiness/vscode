         reason = "environment variable 'no-cache' is set";
     }
     else if (r->no_cache) {
         /* or we've been asked not to cache it above */
         reason = "r->no_cache present";
     }
+    else if (cache->stale_handle
+            && APR_DATE_BAD
+                    != (date = apr_date_parse_http(
+                            apr_table_get(r->headers_out, "Date")))
+            && date < cache->stale_handle->cache_obj->info.date) {
 
-    /* Hold the phone. Some servers might allow us to cache a 2xx, but
-     * then make their 304 responses non cacheable. This leaves us in a
-     * sticky position. If the 304 is in answer to our own conditional
-     * request, we cannot send this 304 back to the client because the
-     * client isn't expecting it. Instead, our only option is to respect
-     * the answer to the question we asked (has it changed, answer was
-     * no) and return the cached item to the client, and then respect
-     * the uncacheable nature of this 304 by allowing the remove_url
-     * filter to kick in and remove the cached entity.
-     */
-    if (reason && r->status == HTTP_NOT_MODIFIED &&
-             cache->stale_handle) {
-        apr_bucket_brigade *bb;
-        apr_bucket *bkt;
-        int status;
-
-        cache->handle = cache->stale_handle;
-        info = &cache->handle->cache_obj->info;
-
-        /* Load in the saved status and clear the status line. */
-        r->status = info->status;
-        r->status_line = NULL;
-
-        bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
+        /**
+         * 13.12 Cache Replacement:
+         *
+         * Note: a new response that has an older Date header value than
+         * existing cached responses is not cacheable.
+         */
+        reason = "updated entity is older than cached entity";
 
-        r->headers_in = cache->stale_headers;
-        status = ap_meets_conditions(r);
-        if (status != OK) {
-            r->status = status;
+        /* while this response is not cacheable, the previous response still is */
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00770)
+                "cache: Removing CACHE_REMOVE_URL filter.");
+        ap_remove_output_filter(cache->remove_url_filter);
+    }
+    else if (r->status == HTTP_NOT_MODIFIED && cache->stale_handle) {
+        apr_table_t *left = cache->stale_handle->resp_hdrs;
+        apr_table_t *right = r->headers_out;
 
-            bkt = apr_bucket_flush_create(bb->bucket_alloc);
-            APR_BRIGADE_INSERT_TAIL(bb, bkt);
+        /* and lastly, contradiction checks for revalidated responses
+         * as per RFC2616 Section 10.3.5
+         */
+        if (((reason = cache_header_cmp(r->pool, left, right, "Allow")))
+                || ((reason = cache_header_cmp(r->pool, left, right,
+                        "Content-Encoding")))
+                || ((reason = cache_header_cmp(r->pool, left, right,
+                        "Content-Language")))
+                || ((reason = cache_header_cmp(r->pool, left, right,
+                        "Content-Length")))
+                || ((reason = cache_header_cmp(r->pool, left, right,
+                        "Content-Location")))
+                || ((reason = cache_header_cmp(r->pool, left, right,
+                        "Content-MD5")))
+                || ((reason = cache_header_cmp(r->pool, left, right,
+                        "Content-Range")))
+                || ((reason = cache_header_cmp(r->pool, left, right,
+                        "Content-Type")))
+                || ((reason = cache_header_cmp(r->pool, left, right, "Expires")))
+                || ((reason = cache_header_cmp(r->pool, left, right, "ETag")))
+                || ((reason = cache_header_cmp(r->pool, left, right,
+                        "Last-Modified")))) {
+            /* contradiction: 304 Not Modified, but entity header modified */
         }
-        else {
-            /* RFC 2616 10.3.5 states that entity headers are not supposed
-             * to be in the 304 response.  Therefore, we need to combine the
-             * response headers with the cached headers *before* we update
-             * the cached headers.
-             *
-             * However, before doing that, we need to first merge in
-             * err_headers_out and we also need to strip any hop-by-hop
-             * headers that might have snuck in.
-             */
-            r->headers_out = ap_cache_cacheable_headers_out(r);
-
-            /* Merge in our cached headers.  However, keep any updated values. */
-            cache_accept_headers(cache->handle, r, 1);
+    }
 
-            cache->provider->recall_body(cache->handle, r->pool, bb);
+    /**
+     * Enforce RFC2616 Section 10.3.5, just in case. We caught any
+     * inconsistencies above.
+     *
+     * If the conditional GET used a strong cache validator (see section
+     * 13.3.3), the response SHOULD NOT include other entity-headers.
+     * Otherwise (i.e., the conditional GET used a weak validator), the
+     * response MUST NOT include other entity-headers; this prevents
+     * inconsistencies between cached entity-bodies and updated headers.
+     */
+    if (r->status == HTTP_NOT_MODIFIED) {
+        apr_table_unset(r->headers_out, "Allow");
+        apr_table_unset(r->headers_out, "Content-Encoding");
+        apr_table_unset(r->headers_out, "Content-Language");
+        apr_table_unset(r->headers_out, "Content-Length");
+        apr_table_unset(r->headers_out, "Content-MD5");
+        apr_table_unset(r->headers_out, "Content-Range");
+        apr_table_unset(r->headers_out, "Content-Type");
+        apr_table_unset(r->headers_out, "Last-Modified");
+    }
 
-            bkt = apr_bucket_eos_create(bb->bucket_alloc);
-            APR_BRIGADE_INSERT_TAIL(bb, bkt);
-        }
+    /* Hold the phone. Some servers might allow us to cache a 2xx, but
+     * then make their 304 responses non cacheable. RFC2616 says this:
+     *
+     * If a 304 response indicates an entity not currently cached, then
+     * the cache MUST disregard the response and repeat the request
+     * without the conditional.
+     *
+     * A 304 response with contradictory headers is technically a
+     * different entity, to be safe, we remove the entity from the cache.
+     */
+    if (reason && r->status == HTTP_NOT_MODIFIED && cache->stale_handle) {
 
-        cache->block_response = 1;
+        ap_log_rerror(
+                APLOG_MARK, APLOG_INFO, 0, r, APLOGNO() "cache: %s responded with an uncacheable 304, retrying the request. Reason: %s", r->unparsed_uri, reason);
 
-        /* we've got a cache conditional hit! tell anyone who cares */
-        cache_run_cache_status(
-                cache->handle,
-                r,
-                r->headers_out,
-                AP_CACHE_REVALIDATE,
-                apr_psprintf(
-                        r->pool,
-                        "conditional cache hit: 304 was uncacheable though (%s); entity removed",
+        /* we've got a cache conditional miss! tell anyone who cares */
+        cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_MISS,
+                apr_psprintf(r->pool,
+                        "conditional cache miss: 304 was uncacheable, entity removed: %s",
                         reason));
 
+        /* remove the cached entity immediately, we might cache it again */
+        ap_remove_output_filter(cache->remove_url_filter);
+        cache_remove_url(cache, r);
+
         /* let someone else attempt to cache */
         cache_remove_lock(conf, cache, r, NULL);
 
-        return ap_pass_brigade(f->next, bb);
+        /* remove this filter from the chain */
+        ap_remove_output_filter(f);
+
+        /* retry without the conditionals */
+        apr_table_unset(r->headers_in, "If-Match");
+        apr_table_unset(r->headers_in, "If-Modified-Since");
+        apr_table_unset(r->headers_in, "If-None-Match");
+        apr_table_unset(r->headers_in, "If-Range");
+        apr_table_unset(r->headers_in, "If-Unmodified-Since");
+
+        ap_internal_redirect(r->uri, r);
+
+        return APR_SUCCESS;
     }
 
     if (reason) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00768)
                 "cache: %s not cached. Reason: %s", r->unparsed_uri,
                 reason);
