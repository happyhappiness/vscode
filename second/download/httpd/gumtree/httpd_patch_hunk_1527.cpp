 
         lockname = apr_pstrcat(r->pool, conf->lockpath, dir, "/", lockname, NULL);
     }
     return apr_file_remove(lockname, r->pool);
 }
 
-CACHE_DECLARE(int) ap_cache_check_allowed(request_rec *r) {
-    const char *cc_req;
-    const char *pragma;
-    cache_server_conf *conf =
-      (cache_server_conf *)ap_get_module_config(r->server->module_config,
-                                                &cache_module);
-
-    /*
-     * At this point, we may have data cached, but the request may have
-     * specified that cached data may not be used in a response.
-     *
-     * This is covered under RFC2616 section 14.9.4 (Cache Revalidation and
-     * Reload Controls).
-     *
-     * - RFC2616 14.9.4 End to end reload, Cache-Control: no-cache, or Pragma:
-     * no-cache. The server MUST NOT use a cached copy when responding to such
-     * a request.
-     *
-     * - RFC2616 14.9.2 What May be Stored by Caches. If Cache-Control:
-     * no-store arrives, do not serve from the cache.
-     */
-
-    /* This value comes from the client's initial request. */
-    cc_req = apr_table_get(r->headers_in, "Cache-Control");
-    pragma = apr_table_get(r->headers_in, "Pragma");
-
-    if (ap_cache_liststr(NULL, pragma, "no-cache", NULL)
-        || ap_cache_liststr(NULL, cc_req, "no-cache", NULL)) {
-
-        if (!conf->ignorecachecontrol) {
-            return 0;
-        }
-        else {
-            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
-                         "Incoming request is asking for an uncached version of "
-                         "%s, but we have been configured to ignore it and serve "
-                         "cached content anyway", r->unparsed_uri);
-        }
-    }
-
-    if (ap_cache_liststr(NULL, cc_req, "no-store", NULL)) {
-
-        if (!conf->ignorecachecontrol) {
-            /* We're not allowed to serve a cached copy */
-            return 0;
-        }
-        else {
-            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
-                         "Incoming request is asking for a no-store version of "
-                         "%s, but we have been configured to ignore it and serve "
-                         "cached content anyway", r->unparsed_uri);
-        }
-    }
-
-    return 1;
-}
-
-
 CACHE_DECLARE(int) ap_cache_check_freshness(cache_handle_t *h,
                                             request_rec *r)
 {
     apr_status_t status;
     apr_int64_t age, maxage_req, maxage_cresp, maxage, smaxage, maxstale;
     apr_int64_t minfresh;
