             skip_first = TRUE;
             break;
         }
     }
 
     n = SSL_CTX_use_certificate_chain(mctx->ssl_ctx,
-                                      (char *)chain, 
+                                      (char *)chain,
                                       skip_first, NULL);
     if (n < 0) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                 "Failed to configure CA certificate chain!");
         ssl_die();
     }
