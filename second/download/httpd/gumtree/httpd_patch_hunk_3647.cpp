         X509 *cert;
         int i = 0;
         int ret = SSL_CTX_set_current_cert(sc->server->ssl_ctx,
                                            SSL_CERT_SET_FIRST);
         while (ret) {
             cert = SSL_CTX_get0_certificate(sc->server->ssl_ctx);
-            if (!cert || !ssl_stapling_init_cert(s, sc->server, cert)) {
+            if (!cert || !ssl_stapling_init_cert(s, p, ptemp, sc->server,
+                                                 cert)) {
                 ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02604)
                              "Unable to configure certificate %s:%d "
                              "for stapling", sc->vhost_id, i);
             }
             ret = SSL_CTX_set_current_cert(sc->server->ssl_ctx,
                                            SSL_CERT_SET_NEXT);
