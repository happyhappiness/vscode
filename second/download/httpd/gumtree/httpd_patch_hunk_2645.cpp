         input_ctx->tmp = apr_palloc(r->pool, INPUT_XLATE_BUF_SIZE);
         input_ctx->dc = dc;
         reqinfo->input_ctx = input_ctx;
         rv = apr_xlate_open(&input_ctx->xlate, dc->charset_source,
                             dc->charset_default, r->pool);
         if (rv != APR_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01449)
                           "can't open translation %s->%s",
                           dc->charset_default, dc->charset_source);
             return HTTP_INTERNAL_SERVER_ERROR;
         }
         if (apr_xlate_sb_get(input_ctx->xlate, &input_ctx->is_sb) != APR_SUCCESS) {
             input_ctx->is_sb = 0;
