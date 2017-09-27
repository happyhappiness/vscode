     /*
      * Create a new SSL connection with the configured server SSL context and
      * attach this to the socket. Additionally we register this attachment
      * so we can detach later.
      */
     if (!(ssl = SSL_new(mctx->ssl_ctx))) {
-        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(01962)
                       "Unable to create a new SSL connection from the SSL "
                       "context");
         ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, server);
 
         c->aborted = 1;
 
