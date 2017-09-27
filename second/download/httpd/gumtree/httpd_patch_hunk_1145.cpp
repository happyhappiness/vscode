     char server_portstr[32];
     char *scheme;
     const char *proxy_function;
     const char *u;
     proxy_conn_rec *backend = NULL;
     int is_ssl = 0;
-
-    /* Note: Memory pool allocation.
-     * A downstream keepalive connection is always connected to the existence
-     * (or not) of an upstream keepalive connection. If this is not done then
-     * load balancing against multiple backend servers breaks (one backend
-     * server ends up taking 100% of the load), and the risk is run of
-     * downstream keepalive connections being kept open unnecessarily. This
-     * keeps webservers busy and ties up resources.
-     *
-     * As a result, we allocate all sockets out of the upstream connection
-     * pool, and when we want to reuse a socket, we check first whether the
-     * connection ID of the current upstream connection is the same as that
-     * of the connection when the socket was opened.
-     */
-    apr_pool_t *p = r->connection->pool;
     conn_rec *c = r->connection;
-    apr_uri_t *uri = apr_palloc(r->connection->pool, sizeof(*uri));
+    /*
+     * Use a shorter-lived pool to reduce memory usage
+     * and avoid a memory leak
+     */
+    apr_pool_t *p = r->pool;
+    apr_uri_t *uri = apr_palloc(p, sizeof(*uri));
 
     /* find the scheme */
     u = strchr(url, ':');
     if (u == NULL || u[1] != '/' || u[2] != '/' || u[3] == '\0')
        return DECLINED;
     if ((u - url) > 14)
         return HTTP_BAD_REQUEST;
-    scheme = apr_pstrndup(c->pool, url, u - url);
+    scheme = apr_pstrndup(p, url, u - url);
     /* scheme is lowercase */
     ap_str_tolower(scheme);
     /* is it for us? */
     if (strcmp(scheme, "https") == 0) {
         if (!ap_proxy_ssl_enable(NULL)) {
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
