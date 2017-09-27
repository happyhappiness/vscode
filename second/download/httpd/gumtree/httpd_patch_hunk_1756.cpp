                                   "could not read bucket for SSL buffer");
                     return HTTP_INTERNAL_SERVER_ERROR;
                 }
                 total += len;
             }
 
-            rv = apr_bucket_setaside(e, ctx->pool);
+            rv = apr_bucket_setaside(e, r->pool);
             if (rv != APR_SUCCESS) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                               "could not setaside bucket for SSL buffer");
                 return HTTP_INTERNAL_SERVER_ERROR;
             }
 
             APR_BUCKET_REMOVE(e);
             APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
         }
 
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, c,
                       "total of %" APR_OFF_T_FMT " bytes in buffer, eos=%d",
                       total, eos);
 
         /* Fail if this exceeds the maximum buffer size. */
         if (total > maxlen) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
