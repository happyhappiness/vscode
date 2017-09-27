             /* ensure that the SSL structures etc are freed, etc: */
             ssl_filter_io_shutdown(filter_ctx, c, 1);
             apr_table_setn(c->notes, "SSL_connect_rv", "err");
             return MODSSL_ERROR_BAD_GATEWAY;
         }
 
+        cert = SSL_get_peer_certificate(filter_ctx->pssl);
+
         if (sc->proxy_ssl_check_peer_expire != SSL_ENABLED_FALSE) {
-            cert = SSL_get_peer_certificate(filter_ctx->pssl);
             if (!cert
                 || (X509_cmp_current_time(
                      X509_get_notBefore(cert)) >= 0)
                 || (X509_cmp_current_time(
                      X509_get_notAfter(cert)) <= 0)) {
+                proxy_ssl_check_peer_ok = FALSE;
                 ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02004)
                               "SSL Proxy: Peer certificate is expired");
-                if (cert) {
-                    X509_free(cert);
-                }
-                /* ensure that the SSL structures etc are freed, etc: */
-                ssl_filter_io_shutdown(filter_ctx, c, 1);
-                apr_table_setn(c->notes, "SSL_connect_rv", "err");
-                return HTTP_BAD_GATEWAY;
             }
-            X509_free(cert);
         }
-        if ((sc->proxy_ssl_check_peer_cn != SSL_ENABLED_FALSE) &&
+        if ((sc->proxy_ssl_check_peer_name != SSL_ENABLED_FALSE) &&
+            hostname_note) {
+            apr_table_unset(c->notes, "proxy-request-hostname");
+            if (!cert
+                || SSL_X509_match_name(c->pool, cert, hostname_note,
+                                       TRUE, server) == FALSE) {
+                proxy_ssl_check_peer_ok = FALSE;
+                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02411)
+                              "SSL Proxy: Peer certificate does not match "
+                              "for hostname %s", hostname_note);
+            }
+        }
+        else if ((sc->proxy_ssl_check_peer_cn != SSL_ENABLED_FALSE) &&
             hostname_note) {
             const char *hostname;
             int match = 0;
 
             hostname = ssl_var_lookup(NULL, server, c, NULL,
                                       "SSL_CLIENT_S_DN_CN");
