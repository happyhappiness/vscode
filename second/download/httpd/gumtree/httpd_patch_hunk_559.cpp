     }
 
     /*
      * Get the SSL connection structure and perform the
      * delayed interlinking from SSL back to request_rec
      */
-    if ((ssl = sslconn->ssl)) {
-        SSL_set_app_data2(ssl, r);
+    ssl = sslconn->ssl;
+    if (!ssl) {
+        return DECLINED;
+    }
+    SSL_set_app_data2(ssl, r);
+
+    /*
+     * Log information about incoming HTTPS requests
+     */
+    if (r->server->loglevel >= APLOG_INFO && ap_is_initial_req(r)) {
+        ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
+                     "%s HTTPS request received for child %ld (server %s)",
+                     (r->connection->keepalives <= 0 ?
+                     "Initial (No.1)" :
+                     apr_psprintf(r->pool, "Subsequent (No.%d)",
+                                  r->connection->keepalives+1)),
+                     r->connection->id,
+                     ssl_util_vhostid(r->pool, r->server));
+    }
+
+    /* SetEnvIf ssl-*-shutdown flags can only be per-server,
+     * so they won't change across keepalive requests
+     */
+    if (sslconn->shutdown_type == SSL_SHUTDOWN_TYPE_UNSET) {
+        ssl_configure_env(r, sslconn);
     }
 
     return DECLINED;
 }
 
 /*
