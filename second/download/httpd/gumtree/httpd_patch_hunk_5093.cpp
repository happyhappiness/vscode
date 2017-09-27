     filter_ctx->pOutputFilter   = ap_add_output_filter(ssl_io_filter,
                                                        filter_ctx, r, c);
 
     filter_ctx->pbioWrite       = BIO_new(&bio_filter_out_method);
     filter_ctx->pbioWrite->ptr  = (void *)bio_filter_out_ctx_new(filter_ctx, c);
 
-    /* We insert a clogging input filter. Let the core know. */
-    c->clogging_input_filters = 1;
+    /* write is non blocking for the benefit of async mpm */
+    if (c->cs) {
+        BIO_set_nbio(filter_ctx->pbioWrite, 1);
+    }
 
     ssl_io_input_add_filter(filter_ctx, c, r, ssl);
 
     SSL_set_bio(ssl, filter_ctx->pbioRead, filter_ctx->pbioWrite);
     filter_ctx->pssl            = ssl;
 
