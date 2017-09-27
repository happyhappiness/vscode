             /*
              * This is in addition to what was present earlier. It is
              * borrowed from openssl_state_machine.c [mod_tls].
              * TBD.
              */
             outctx->rc = APR_EAGAIN;
-            return SSL_ERROR_WANT_READ;
+            return APR_EAGAIN;
         }
         else if (ERR_GET_LIB(ERR_peek_error()) == ERR_LIB_SSL &&
                  ERR_GET_REASON(ERR_peek_error()) == SSL_R_HTTP_REQUEST) {
             /*
              * The case where OpenSSL has recognized a HTTP request:
              * This means the client speaks plain HTTP on our HTTPS port.
              * ssl_io_filter_error will disable the ssl filters when it
              * sees this status code.
              */
-            return HTTP_BAD_REQUEST;
+            return MODSSL_ERROR_HTTP_ON_HTTPS;
         }
         else if (ssl_err == SSL_ERROR_SYSCALL) {
-            ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c,
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rc, c,
                           "SSL handshake interrupted by system "
                           "[Hint: Stop button pressed in browser?!]");
         }
         else /* if (ssl_err == SSL_ERROR_SSL) */ {
             /*
              * Log SSL errors and any unexpected conditions.
              */
             ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c,
                           "SSL library error %d in handshake "
                           "(server %s)", ssl_err,
                           ssl_util_vhostid(c->pool, server));
-            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, server);
+            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, server);
 
         }
         if (inctx->rc == APR_SUCCESS) {
             inctx->rc = APR_EGENERAL;
         }
 
-        return ssl_filter_io_shutdown(filter_ctx, c, 1);
+        ssl_filter_io_shutdown(filter_ctx, c, 1);
+        return inctx->rc;
     }
     sc = mySrvConfig(sslconn->server);
 
     /*
      * Check for failed client authentication
      */
