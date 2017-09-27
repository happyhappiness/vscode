         return APR_SUCCESS;
     }
 
     ap_ssi_get_tag_and_value(ctx, &tag, &expr, SSI_VALUE_RAW);
 
     if (strcmp(tag, "expr")) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter \"%s\" "
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01354) "unknown parameter \"%s\" "
                       "to tag if in %s", tag, r->filename);
         SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
         return APR_SUCCESS;
     }
 
     if (!expr) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "missing expr value for if "
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01355) "missing expr value for if "
                       "element in %s", r->filename);
         SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
         return APR_SUCCESS;
     }
 
     DEBUG_PRINTF((ctx, "****    if expr=\"%s\"\n", expr));
 
-    expr_ret = ap_expr_evalstring(r, expr, &was_error, &ctx->intern->re,
-                                  ssi_parse_string, ctx->intern->access_func);
+    if (ctx->intern->legacy_expr)
+        expr_ret = parse_expr(ctx, expr, &was_error);
+    else
+        expr_ret = parse_ap_expr(ctx, expr, &was_error);
 
     if (was_error) {
         SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
         return APR_SUCCESS;
     }
 
