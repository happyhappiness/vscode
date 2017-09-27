             ctx = f->ctx = apr_pcalloc(f->r->pool, sizeof(charset_filter_ctx_t));
             ctx->dc = dc;
             ctx->noop = 1;
         }
     }
 
-    if (dc->debug >= DBGLVL_GORY) {
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
-                     "xlate_in_filter() - "
-                     "charset_source: %s charset_default: %s",
-                     dc && dc->charset_source ? dc->charset_source : "(none)",
-                     dc && dc->charset_default ? dc->charset_default : "(none)");
-    }
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE6, 0, f->r,
+                 "xlate_in_filter() - "
+                 "charset_source: %s charset_default: %s",
+                 dc && dc->charset_source ? dc->charset_source : "(none)",
+                 dc && dc->charset_default ? dc->charset_default : "(none)");
 
     if (!ctx->ran) {  /* filter never ran before */
         chk_filter_chain(f);
         ctx->ran = 1;
         if (!ctx->noop && !ctx->is_sb
             && apr_table_get(f->r->headers_in, "Content-Length")) {
