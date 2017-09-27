             else /* if (ssl_err == SSL_ERROR_SSL) */ {
                 /*
                  * Log SSL errors and any unexpected conditions.
                  */
                 ap_log_cerror(APLOG_MARK, APLOG_INFO, inctx->rc, c,
                               "SSL library error %d reading data", ssl_err);
-                ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, mySrvFromConn(c));
+                ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, mySrvFromConn(c));
 
             }
             if (inctx->rc == APR_SUCCESS) {
                 inctx->rc = APR_EGENERAL;
             }
             break;
         }
     }
     return inctx->rc;
 }
 
+/* Read a line of input from the SSL input layer into buffer BUF of
+ * length *LEN; updating *len to reflect the length of the line
+ * including the LF character. */
 static apr_status_t ssl_io_input_getline(bio_filter_in_ctx_t *inctx,
                                          char *buf,
                                          apr_size_t *len)
 {
     const char *pos = NULL;
     apr_status_t status;
