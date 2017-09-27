     proxy_conn_rec *backend = NULL;
     char *scheme;
     int retry;
     conn_rec *c = r->connection;
     apr_pool_t *p = r->pool;
     apr_uri_t *uri;
+    int is_ssl = 0;
 
     if (strncasecmp(url, "wss:", 4) == 0) {
         scheme = "WSS";
+        is_ssl = 1;
     }
     else if (strncasecmp(url, "ws:", 3) == 0) {
         scheme = "WS";
     }
     else {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02450) "declining URL %s", url);
