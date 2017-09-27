         if (rv != APR_SUCCESS) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                           "can't open translation %s->%s",
                           dc->charset_default, dc->charset_source);
             return HTTP_INTERNAL_SERVER_ERROR;
         }
+        if (apr_xlate_sb_get(input_ctx->xlate, &input_ctx->is_sb) != APR_SUCCESS) {
+            input_ctx->is_sb = 0;
+        }
     }
 
     return DECLINED;
 }
 
 static int configured_in_list(request_rec *r, const char *filter_name,
