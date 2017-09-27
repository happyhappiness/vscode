              * (This is usually the case when the client forces an SSL
              * renegotation which is handled implicitly by OpenSSL.)
              */
             outctx->rc = APR_EAGAIN;
         }
         else if (ssl_err == SSL_ERROR_SYSCALL) {
-            ap_log_error(APLOG_MARK, APLOG_INFO, outctx->rc, c->base_server,
-                        "SSL output filter write failed.");
+            ap_log_cerror(APLOG_MARK, APLOG_INFO, outctx->rc, c,
+                          "SSL output filter write failed.");
         }
         else /* if (ssl_err == SSL_ERROR_SSL) */ {
             /*
              * Log SSL errors
              */
-            ap_log_error(APLOG_MARK, APLOG_INFO, outctx->rc, c->base_server,
-                         "SSL library error %d writing data", ssl_err);
+            ap_log_cerror(APLOG_MARK, APLOG_INFO, outctx->rc, c,
+                          "SSL library error %d writing data", ssl_err);
             ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
         }
         if (outctx->rc == APR_SUCCESS) {
             outctx->rc = APR_EGENERAL;
         }
     }
