     inctx->bb = apr_brigade_create(c->pool, c->bucket_alloc);
     inctx->block = APR_BLOCK_READ;
     inctx->pool = c->pool;
     inctx->filter_ctx = filter_ctx;
 }
 
-void ssl_io_filter_init(conn_rec *c, SSL *ssl)
+/* The request_rec pointer is passed in here only to ensure that the
+ * filter chain is modified correctly when doing a TLS upgrade.  It
+ * must *not* be used otherwise. */
+void ssl_io_filter_init(conn_rec *c, request_rec *r, SSL *ssl)
 {
     ssl_filter_ctx_t *filter_ctx;
 
     filter_ctx = apr_palloc(c->pool, sizeof(ssl_filter_ctx_t));
 
     filter_ctx->config          = myConnConfig(c);
 
     filter_ctx->nobuffer        = 0;
     filter_ctx->pOutputFilter   = ap_add_output_filter(ssl_io_filter,
-                                                   filter_ctx, NULL, c);
+                                                       filter_ctx, r, c);
 
     filter_ctx->pbioWrite       = BIO_new(&bio_filter_out_method);
     filter_ctx->pbioWrite->ptr  = (void *)bio_filter_out_ctx_new(filter_ctx, c);
 
     /* We insert a clogging input filter. Let the core know. */
     c->clogging_input_filters = 1;
-    
-    ssl_io_input_add_filter(filter_ctx, c, ssl);
+
+    ssl_io_input_add_filter(filter_ctx, c, r, ssl);
 
     SSL_set_bio(ssl, filter_ctx->pbioRead, filter_ctx->pbioWrite);
     filter_ctx->pssl            = ssl;
 
     apr_pool_cleanup_register(c->pool, (void*)filter_ctx,
                               ssl_io_filter_cleanup, apr_pool_cleanup_null);
 
-    if (c->base_server->loglevel >= APLOG_DEBUG) {
+    if (APLOGctrace4(c)) {
         BIO_set_callback(SSL_get_rbio(ssl), ssl_io_data_cb);
         BIO_set_callback_arg(SSL_get_rbio(ssl), (void *)ssl);
     }
 
     return;
 }
 
 void ssl_io_filter_register(apr_pool_t *p)
 {
-    /* This filter MUST be after the HTTP_HEADER filter, but it also must be
-     * a resource-level filter so it has the request_rec.
-     */
-    ap_register_output_filter ("UPGRADE_FILTER", ssl_io_filter_Upgrade, NULL, AP_FTYPE_PROTOCOL + 5);
-
     ap_register_input_filter  (ssl_io_filter, ssl_io_filter_input,  NULL, AP_FTYPE_CONNECTION + 5);
     ap_register_output_filter (ssl_io_filter, ssl_io_filter_output, NULL, AP_FTYPE_CONNECTION + 5);
 
     ap_register_input_filter  (ssl_io_buffer, ssl_io_filter_buffer, NULL, AP_FTYPE_PROTOCOL);
 
     return;
