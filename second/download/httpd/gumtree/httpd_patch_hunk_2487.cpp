         b = apr_bucket_flush_create(c->bucket_alloc);
         APR_BRIGADE_INSERT_TAIL(bb, b);
         rv = ap_pass_brigade(r->output_filters, bb);
         cid->response_sent = 1;
         if (rv != APR_SUCCESS)
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
-                          "ISAPI: WriteClient ap_pass_brigade "
-                          "failed: %s", r->filename);
+                          "WriteClient ap_pass_brigade failed: %s",
+                          r->filename);
     }
 
     if ((flags & HSE_IO_ASYNC) && cid->completion) {
         if (rv == APR_SUCCESS) {
             cid->completion(cid->ecb, cid->completion_arg,
                             *size_arg, ERROR_SUCCESS);
