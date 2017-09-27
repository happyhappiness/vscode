             ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01897)
                          "Init: Oops, you want to request client "
                          "authentication, but no CAs are known for "
                          "verification!?  [Hint: SSLCACertificate*]");
         }
     }
+
+    return APR_SUCCESS;
 }
 
-static void ssl_init_ctx_cipher_suite(server_rec *s,
-                                      apr_pool_t *p,
-                                      apr_pool_t *ptemp,
-                                      modssl_ctx_t *mctx)
+static apr_status_t ssl_init_ctx_cipher_suite(server_rec *s,
+                                              apr_pool_t *p,
+                                              apr_pool_t *ptemp,
+                                              modssl_ctx_t *mctx)
 {
     SSL_CTX *ctx = mctx->ssl_ctx;
     const char *suite;
 
     /*
      *  Configure SSL Cipher Suite. Always disable NULL and export ciphers,
