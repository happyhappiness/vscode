         else /* if (ssl_err == SSL_ERROR_SSL) */ {
             /*
              * Log SSL errors
              */
             ap_log_cerror(APLOG_MARK, APLOG_INFO, outctx->rc, c,
                           "SSL library error %d writing data", ssl_err);
-            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, mySrvFromConn(c));
+            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, mySrvFromConn(c));
         }
         if (outctx->rc == APR_SUCCESS) {
             outctx->rc = APR_EGENERAL;
         }
     }
     else if ((apr_size_t)res != len) {
