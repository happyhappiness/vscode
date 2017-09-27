 static void ssl_init_ctx_cipher_suite(server_rec *s,
                                       apr_pool_t *p,
                                       apr_pool_t *ptemp,
                                       modssl_ctx_t *mctx)
 {
     SSL_CTX *ctx = mctx->ssl_ctx;
-    const char *suite = mctx->auth.cipher_suite;
+    const char *suite;
 
     /*
-     *  Configure SSL Cipher Suite
+     *  Configure SSL Cipher Suite. Always disable NULL and export ciphers,
+     *  see also ssl_engine_config.c:ssl_cmd_SSLCipherSuite().
+     *  OpenSSL's SSL_DEFAULT_CIPHER_LIST already includes !aNULL:!eNULL,
+     *  so only prepend !EXP in this case.
      */
-    if (!suite) {
-        return;
-    }
+    suite = mctx->auth.cipher_suite ? mctx->auth.cipher_suite :
+            apr_pstrcat(ptemp, "!EXP:", SSL_DEFAULT_CIPHER_LIST, NULL);
 
     ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                  "Configuring permitted SSL ciphers [%s]",
                  suite);
 
     if (!SSL_CTX_set_cipher_list(ctx, suite)) {
