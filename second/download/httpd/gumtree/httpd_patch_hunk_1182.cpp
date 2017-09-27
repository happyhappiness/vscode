  * ap_hook_process_connection hook.
  */
 static int ssl_io_filter_connect(ssl_filter_ctx_t *filter_ctx)
 {
     conn_rec *c         = (conn_rec *)SSL_get_app_data(filter_ctx->pssl);
     SSLConnRec *sslconn = myConnConfig(c);
-    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
+    SSLSrvConfigRec *sc;
     X509 *cert;
     int n;
     int ssl_err;
     long verify_result;
+    server_rec *server;
 
     if (SSL_is_init_finished(filter_ctx->pssl)) {
         return APR_SUCCESS;
     }
 
+    server = sslconn->server;
     if (sslconn->is_proxy) {
+        const char *hostname_note;
+
+        sc = mySrvConfig(server);
         if ((n = SSL_connect(filter_ctx->pssl)) <= 0) {
             ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                           "SSL Proxy connect failed");
-            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
+            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, server);
             /* ensure that the SSL structures etc are freed, etc: */
             ssl_filter_io_shutdown(filter_ctx, c, 1);
             return HTTP_BAD_GATEWAY;
         }
 
+        if (sc->proxy_ssl_check_peer_expire == SSL_ENABLED_TRUE) {
+            cert = SSL_get_peer_certificate(filter_ctx->pssl);
+            if (!cert
+                || (X509_cmp_current_time(
+                     X509_get_notBefore(cert)) >= 0)
+                || (X509_cmp_current_time(
+                     X509_get_notAfter(cert)) <= 0)) {
+                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
+                              "SSL Proxy: Peer certificate is expired");
+                if (cert) {
+                    X509_free(cert);
+                }
+                /* ensure that the SSL structures etc are freed, etc: */
+                ssl_filter_io_shutdown(filter_ctx, c, 1);
+                return HTTP_BAD_GATEWAY;
+            }
+            X509_free(cert);
+        }
+        if ((sc->proxy_ssl_check_peer_cn == SSL_ENABLED_TRUE)
+            && ((hostname_note =
+                 apr_table_get(c->notes, "proxy-request-hostname")) != NULL)) {
+            const char *hostname;
+
+            hostname = ssl_var_lookup(NULL, server, c, NULL,
+                                      "SSL_CLIENT_S_DN_CN");
+            apr_table_unset(c->notes, "proxy-request-hostname");
+            if (strcasecmp(hostname, hostname_note)) {
+                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
+                              "SSL Proxy: Peer certificate CN mismatch:"
+                              " Certificate CN: %s Requested hostname: %s",
+                              hostname, hostname_note);
+                /* ensure that the SSL structures etc are freed, etc: */
+                ssl_filter_io_shutdown(filter_ctx, c, 1);
+                return HTTP_BAD_GATEWAY;
+            }
+        }
+
         return APR_SUCCESS;
     }
 
     if ((n = SSL_accept(filter_ctx->pssl)) <= 0) {
         bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)
                                      (filter_ctx->pbioRead->ptr);
