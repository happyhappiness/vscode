                              "stapling_cb: fatal error renewing response");
                 return SSL_TLSEXT_ERR_ALERT_FATAL;
             }
         }
     }
 
-    if (rsp) {
+    if (rsp && ((ok == TRUE) || (mctx->stapling_return_errors == TRUE))) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01956)
                      "stapling_cb: setting response");
         if (!stapling_set_response(ssl, rsp))
             return SSL_TLSEXT_ERR_ALERT_FATAL;
         return SSL_TLSEXT_ERR_OK;
     }
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01957)
-                 "stapling_cb: no response available");
+                 "stapling_cb: no suitable response available");
 
     return SSL_TLSEXT_ERR_NOACK;
 
 }
 
 apr_status_t modssl_init_stapling(server_rec *s, apr_pool_t *p,
