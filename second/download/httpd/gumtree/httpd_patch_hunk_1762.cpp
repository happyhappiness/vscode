 
 static void ssl_configure_env(request_rec *r, SSLConnRec *sslconn);
 #ifndef OPENSSL_NO_TLSEXT
 static int ssl_find_vhost(void *servername, conn_rec *c, server_rec *s);
 #endif
 
+#define SWITCH_STATUS_LINE "HTTP/1.1 101 Switching Protocols"
+#define UPGRADE_HEADER "Upgrade: TLS/1.0, HTTP/1.1"
+#define CONNECTION_HEADER "Connection: Upgrade"
+
+/* Perform an upgrade-to-TLS for the given request, per RFC 2817. */
+static apr_status_t upgrade_connection(request_rec *r)
+{
+    struct conn_rec *conn = r->connection;
+    apr_bucket_brigade *bb;
+    SSLConnRec *sslconn;
+    apr_status_t rv;
+    SSL *ssl;
+
+    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, 
+                  "upgrading connection to TLS");
+
+    bb = apr_brigade_create(r->pool, conn->bucket_alloc);
+
+    rv = ap_fputstrs(conn->output_filters, bb, SWITCH_STATUS_LINE, CRLF,
+                     UPGRADE_HEADER, CRLF, CONNECTION_HEADER, CRLF, CRLF, NULL);
+    if (rv == APR_SUCCESS) {
+        APR_BRIGADE_INSERT_TAIL(bb,
+                                apr_bucket_flush_create(conn->bucket_alloc));
+        rv = ap_pass_brigade(conn->output_filters, bb);
+    }
+
+    if (rv) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                      "failed to send 101 interim response for connection "
+                      "upgrade");
+        return rv;
+    }
+
+    ssl_init_ssl_connection(conn, r);
+    
+    sslconn = myConnConfig(conn);
+    ssl = sslconn->ssl;
+    
+    /* Perform initial SSL handshake. */
+    SSL_set_accept_state(ssl);
+    SSL_do_handshake(ssl);
+
+    if (SSL_get_state(ssl) != SSL_ST_OK) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                      "TLS upgrade handshake failed: not accepted by client!?");
+        
+        return APR_ECONNABORTED;
+    }
+
+    return APR_SUCCESS;
+}
+
 /* Perform a speculative (and non-blocking) read from the connection
  * filters for the given request, to determine whether there is any
  * pending data to read.  Return non-zero if there is, else zero. */
 static int has_buffered_data(request_rec *r) 
 {
     apr_bucket_brigade *bb;
