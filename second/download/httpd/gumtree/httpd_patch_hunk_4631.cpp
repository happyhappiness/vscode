 #define MODSSL_ERROR_HTTP_ON_HTTPS (APR_OS_START_USERERR + 0)
 
 /* Custom apr_status_t error code, used when the proxy cannot
  * establish an outgoing SSL connection. */
 #define MODSSL_ERROR_BAD_GATEWAY (APR_OS_START_USERERR + 1)
 
-static void ssl_io_filter_disable(SSLConnRec *sslconn, ap_filter_t *f)
+static void ssl_io_filter_disable(SSLConnRec *sslconn,
+                                  bio_filter_in_ctx_t *inctx)
 {
-    bio_filter_in_ctx_t *inctx = f->ctx;
     SSL_free(inctx->ssl);
     sslconn->ssl = NULL;
     inctx->ssl = NULL;
     inctx->filter_ctx->pssl = NULL;
 }
 
-static apr_status_t ssl_io_filter_error(ap_filter_t *f,
+static apr_status_t ssl_io_filter_error(bio_filter_in_ctx_t *inctx,
                                         apr_bucket_brigade *bb,
                                         apr_status_t status,
                                         int is_init)
 {
+    ap_filter_t *f = inctx->f;
     SSLConnRec *sslconn = myConnConfig(f->c);
     apr_bucket *bucket;
     int send_eos = 1;
 
     switch (status) {
     case MODSSL_ERROR_HTTP_ON_HTTPS:
             /* log the situation */
             ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c, APLOGNO(01996)
                          "SSL handshake failed: HTTP spoken on HTTPS port; "
                          "trying to send HTML error page");
             ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, sslconn->server);
 
-            ssl_io_filter_disable(sslconn, f);
+            ssl_io_filter_disable(sslconn, inctx);
             f->c->keepalive = AP_CONN_CLOSE;
             if (is_init) {
                 sslconn->non_ssl_request = NON_SSL_SEND_REQLINE;
                 return APR_EGENERAL;
             }
             sslconn->non_ssl_request = NON_SSL_SEND_HDR_SEP;
