             break;
     }
 
     if (f == NULL) {
         /* our filter hasn't been added yet */
         ctx = apr_pcalloc(r->pool, sizeof(*ctx));
+        ctx->tmpbb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
+
         ap_add_output_filter("OLD_WRITE", ctx, r, r->connection);
         f = r->output_filters;
     }
 
+    return f;
+}
+
+static apr_status_t buffer_output(request_rec *r,
+                                  const char *str, apr_size_t len)
+{
+    conn_rec *c = r->connection;
+    ap_filter_t *f;
+    old_write_filter_ctx *ctx;
+
+    if (len == 0)
+        return APR_SUCCESS;
+
+    f = insert_old_write_filter(r);
+    ctx = f->ctx;
+
     /* if the first filter is not our buffering filter, then we have to
      * deliver the content through the normal filter chain
      */
     if (f != r->output_filters) {
-        apr_bucket_brigade *bb = apr_brigade_create(r->pool, c->bucket_alloc);
+        apr_status_t rv;
         apr_bucket *b = apr_bucket_transient_create(str, len, c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(bb, b);
+        APR_BRIGADE_INSERT_TAIL(ctx->tmpbb, b);
 
-        return ap_pass_brigade(r->output_filters, bb);
+        rv = ap_pass_brigade(r->output_filters, ctx->tmpbb);
+        apr_brigade_cleanup(ctx->tmpbb);
+        return rv;
     }
 
-    /* grab the context from our filter */
-    ctx = r->output_filters->ctx;
-
     if (ctx->bb == NULL) {
         ctx->bb = apr_brigade_create(r->pool, c->bucket_alloc);
     }
 
     return ap_fwrite(f->next, ctx->bb, str, len);
 }
