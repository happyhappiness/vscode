     }
     do {
         apr_bucket *bucket;
 
         rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                             APR_BLOCK_READ, HUGE_STRING_LEN);
-       
+
         if (rv != APR_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                          "Error reading request entity data");
-            return HTTP_INTERNAL_SERVER_ERROR;
+            return rv;
         }
 
-        APR_BRIGADE_FOREACH(bucket, bb) {
+        for (bucket = APR_BRIGADE_FIRST(bb);
+             bucket != APR_BRIGADE_SENTINEL(bb);
+             bucket = APR_BUCKET_NEXT(bucket))
+        {
             const char *data;
             apr_size_t len;
 
             if (APR_BUCKET_IS_EOS(bucket)) {
                 seen_eos = 1;
                 break;
