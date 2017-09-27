     }
 
     ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                  "Configuring permitted SSL ciphers [%s]",
                  suite);
 
-    if (!SSL_CTX_set_cipher_list(ctx, MODSSL_PCHAR_CAST suite)) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+    if (!SSL_CTX_set_cipher_list(ctx, suite)) {
+        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01898)
                 "Unable to configure permitted SSL ciphers");
-        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
+        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
         ssl_die();
     }
 }
 
 static void ssl_init_ctx_crl(server_rec *s,
                              apr_pool_t *p,
                              apr_pool_t *ptemp,
                              modssl_ctx_t *mctx)
 {
+    X509_STORE *store = SSL_CTX_get_cert_store(mctx->ssl_ctx);
+    unsigned long crlflags = 0;
+    char *cfgp = mctx->pkp ? "SSLProxy" : "SSL";
+
     /*
      * Configure Certificate Revocation List (CRL) Details
      */
 
     if (!(mctx->crl_file || mctx->crl_path)) {
+        if (mctx->crl_check_mode == SSL_CRLCHECK_LEAF ||
+            mctx->crl_check_mode == SSL_CRLCHECK_CHAIN) {
+            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01899)
+                         "Host %s: CRL checking has been enabled, but "
+                         "neither %sCARevocationFile nor %sCARevocationPath "
+                         "is configured", mctx->sc->vhost_id, cfgp, cfgp);
+            ssl_die();
+        }
         return;
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01900)
                  "Configuring certificate revocation facility");
 
-    mctx->crl =
-        SSL_X509_STORE_create((char *)mctx->crl_file,
-                              (char *)mctx->crl_path);
-
-    if (!mctx->crl) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
-                "Unable to configure X.509 CRL storage "
-                "for certificate revocation");
-        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
+    if (!store || !X509_STORE_load_locations(store, mctx->crl_file,
+                                             mctx->crl_path)) {
+        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01901)
+                     "Host %s: unable to configure X.509 CRL storage "
+                     "for certificate revocation", mctx->sc->vhost_id);
+        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
         ssl_die();
     }
+
+    switch (mctx->crl_check_mode) {
+       case SSL_CRLCHECK_LEAF:
+           crlflags = X509_V_FLAG_CRL_CHECK;
+           break;
+       case SSL_CRLCHECK_CHAIN:
+           crlflags = X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL;
+           break;
+       default:
+           crlflags = 0;
+    }
+
+    if (crlflags) {
+        X509_STORE_set_flags(store, crlflags);
+    } else {
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01902)
+                     "Host %s: X.509 CRL storage locations configured, "
+                     "but CRL checking (%sCARevocationCheck) is not "
+                     "enabled", mctx->sc->vhost_id, cfgp);
+    }
 }
 
 static void ssl_init_ctx_pkcs7_cert_chain(server_rec *s, modssl_ctx_t *mctx)
 {
     STACK_OF(X509) *certs = ssl_read_pkcs7(s, mctx->pkcs7);
     int n;
+    STACK_OF(X509) *extra_certs = NULL;
+
+#ifdef OPENSSL_NO_SSL_INTERN
+    SSL_CTX_get_extra_chain_certs(mctx->ssl_ctx, &extra_certs);
+#else
+    extra_certs = mctx->ssl_ctx->extra_certs;
+#endif
 
-    if (!mctx->ssl_ctx->extra_certs)
+    if (!extra_certs)
         for (n = 1; n < sk_X509_num(certs); ++n)
              SSL_CTX_add_extra_chain_cert(mctx->ssl_ctx, sk_X509_value(certs, n));
 }
 
 static void ssl_init_ctx_cert_chain(server_rec *s,
                                     apr_pool_t *p,
