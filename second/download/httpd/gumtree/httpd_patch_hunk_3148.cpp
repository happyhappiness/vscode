     if (SSL_is_init_finished(filter_ctx->pssl)) {
         return APR_SUCCESS;
     }
 
     server = sslconn->server;
     if (sslconn->is_proxy) {
-        const char *hostname_note;
-
+#ifndef OPENSSL_NO_TLSEXT
+        apr_ipsubnet_t *ip;
+#endif
+        const char *hostname_note = apr_table_get(c->notes,
+                                                  "proxy-request-hostname");
         sc = mySrvConfig(server);
+
+#ifndef OPENSSL_NO_TLSEXT
+        /*
+         * Enable SNI for backend requests. Make sure we don't do it for
+         * pure SSLv3 connections, and also prevent IP addresses
+         * from being included in the SNI extension. (OpenSSL would simply
+         * pass them on, but RFC 6066 is quite clear on this: "Literal
+         * IPv4 and IPv6 addresses are not permitted".)
+         */
+        if (hostname_note &&
+            sc->proxy->protocol != SSL_PROTOCOL_SSLV3 &&
+            apr_ipsubnet_create(&ip, hostname_note, NULL,
+                                c->pool) != APR_SUCCESS) {
+            if (SSL_set_tlsext_host_name(filter_ctx->pssl, hostname_note)) {
+                ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
+                              "SNI extension for SSL Proxy request set to '%s'",
+                              hostname_note);
+            } else {
+                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c, APLOGNO(02002)
+                              "Failed to set SNI extension for SSL Proxy "
+                              "request to '%s'", hostname_note);
+                ssl_log_ssl_error(SSLLOG_MARK, APLOG_WARNING, server);
+            }
+	}
+#endif
+
         if ((n = SSL_connect(filter_ctx->pssl)) <= 0) {
-            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
+            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02003)
                           "SSL Proxy connect failed");
             ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, server);
             /* ensure that the SSL structures etc are freed, etc: */
             ssl_filter_io_shutdown(filter_ctx, c, 1);
+            apr_table_setn(c->notes, "SSL_connect_rv", "err");
             return MODSSL_ERROR_BAD_GATEWAY;
         }
 
         if (sc->proxy_ssl_check_peer_expire != SSL_ENABLED_FALSE) {
             cert = SSL_get_peer_certificate(filter_ctx->pssl);
             if (!cert
                 || (X509_cmp_current_time(
                      X509_get_notBefore(cert)) >= 0)
                 || (X509_cmp_current_time(
                      X509_get_notAfter(cert)) <= 0)) {
-                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
+                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02004)
                               "SSL Proxy: Peer certificate is expired");
                 if (cert) {
                     X509_free(cert);
                 }
                 /* ensure that the SSL structures etc are freed, etc: */
                 ssl_filter_io_shutdown(filter_ctx, c, 1);
+                apr_table_setn(c->notes, "SSL_connect_rv", "err");
                 return HTTP_BAD_GATEWAY;
             }
             X509_free(cert);
         }
-        if ((sc->proxy_ssl_check_peer_cn != SSL_ENABLED_FALSE)
-            && ((hostname_note =
-                 apr_table_get(c->notes, "proxy-request-hostname")) != NULL)) {
+        if ((sc->proxy_ssl_check_peer_cn != SSL_ENABLED_FALSE) &&
+            hostname_note) {
             const char *hostname;
 
             hostname = ssl_var_lookup(NULL, server, c, NULL,
                                       "SSL_CLIENT_S_DN_CN");
             apr_table_unset(c->notes, "proxy-request-hostname");
             if (strcasecmp(hostname, hostname_note)) {
-                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
+                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02005)
                               "SSL Proxy: Peer certificate CN mismatch:"
                               " Certificate CN: %s Requested hostname: %s",
                               hostname, hostname_note);
                 /* ensure that the SSL structures etc are freed, etc: */
                 ssl_filter_io_shutdown(filter_ctx, c, 1);
+                apr_table_setn(c->notes, "SSL_connect_rv", "err");
                 return HTTP_BAD_GATEWAY;
             }
         }
 
+        apr_table_setn(c->notes, "SSL_connect_rv", "ok");
         return APR_SUCCESS;
     }
 
     if ((n = SSL_accept(filter_ctx->pssl)) <= 0) {
         bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)
                                      (filter_ctx->pbioRead->ptr);
