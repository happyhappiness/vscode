 void ssl_io_filter_init(conn_rec *c, SSL *ssl)
 {
     ssl_filter_ctx_t *filter_ctx;
 
     filter_ctx = apr_palloc(c->pool, sizeof(ssl_filter_ctx_t));
 
+    filter_ctx->config          = myConnConfig(c);
+
     filter_ctx->nobuffer        = 0;
     filter_ctx->pOutputFilter   = ap_add_output_filter(ssl_io_filter,
                                                    filter_ctx, NULL, c);
 
     filter_ctx->pbioWrite       = BIO_new(&bio_filter_out_method);
     filter_ctx->pbioWrite->ptr  = (void *)bio_filter_out_ctx_new(filter_ctx, c);
