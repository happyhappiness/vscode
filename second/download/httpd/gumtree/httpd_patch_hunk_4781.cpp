     n = SSL_CTX_use_certificate_chain(mctx->ssl_ctx,
                                       (char *)chain,
                                       skip_first, NULL);
     if (n < 0) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01903)
                 "Failed to configure CA certificate chain!");
-        ssl_die();
+        ssl_die(s);
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01904)
                  "Configuring server certificate chain "
                  "(%d CA certificate%s)",
                  n, n == 1 ? "" : "s");
