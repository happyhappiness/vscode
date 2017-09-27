          * buffered request body has been entirely consumed. */
         if (e == APR_BRIGADE_SENTINEL(bb) || !APR_BUCKET_IS_EOS(e)) {
             e = apr_bucket_eos_create(f->c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(bb, e);
         }
 
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, f->c,
                       "buffered SSL brigade exhausted");
         /* Note that the filter must *not* be removed here; it may be
          * invoked again, see comment above. */
     }
 
     return APR_SUCCESS;
 }
 
+/* The request_rec pointer is passed in here only to ensure that the
+ * filter chain is modified correctly when doing a TLS upgrade.  It
+ * must *not* be used otherwise. */
 static void ssl_io_input_add_filter(ssl_filter_ctx_t *filter_ctx, conn_rec *c,
-                                    SSL *ssl)
+                                    request_rec *r, SSL *ssl)
 {
     bio_filter_in_ctx_t *inctx;
 
     inctx = apr_palloc(c->pool, sizeof(*inctx));
 
-    filter_ctx->pInputFilter = ap_add_input_filter(ssl_io_filter, inctx, NULL, c);
+    filter_ctx->pInputFilter = ap_add_input_filter(ssl_io_filter, inctx, r, c);
 
     filter_ctx->pbioRead = BIO_new(&bio_filter_in_method);
     filter_ctx->pbioRead->ptr = (void *)inctx;
 
     inctx->ssl = ssl;
     inctx->bio_out = filter_ctx->pbioWrite;
