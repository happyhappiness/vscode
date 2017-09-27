                                         apr_pool_t *ptemp,
                                         modssl_ctx_t *mctx)
 {
     /*
      * Configure TLS extensions support
      */
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01893)
                  "Configuring TLS extension handling");
 
     /*
      * Server name indication (SNI)
      */
     if (!SSL_CTX_set_tlsext_servername_callback(mctx->ssl_ctx,
                           ssl_callback_ServerNameIndication) ||
         !SSL_CTX_set_tlsext_servername_arg(mctx->ssl_ctx, mctx)) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01894)
                      "Unable to initialize TLS servername extension "
                      "callback (incompatible OpenSSL version?)");
-        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
+        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
         ssl_die();
     }
 
 #ifdef HAVE_OCSP_STAPLING
     /*
      * OCSP Stapling support, status_request extension
