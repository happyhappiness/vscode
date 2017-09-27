     proxy_conn_rec *backend = NULL;
     apr_pool_t *p = r->pool;
     apr_uri_t *uri = apr_palloc(r->pool, sizeof(*uri));
     char dummy;
 
     if (strncasecmp(url, SCHEME "://", sizeof(SCHEME) + 2)) {
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                      "proxy: " PROXY_FUNCTION ": declining URL %s", url);
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00865)
+                      "declining URL %s", url);
         return DECLINED;
     }
 
     /* Create space for state information */
     status = ap_proxy_acquire_connection(PROXY_FUNCTION, &backend, worker,
                                          r->server);
