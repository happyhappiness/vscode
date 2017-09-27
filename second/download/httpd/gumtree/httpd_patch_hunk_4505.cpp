     {
         if (APR_BUCKET_IS_EOS(b)) {
             eos = b;
             break;
         }
 
+        if (AP_BUCKET_IS_ERROR(b)) {
+            apr_bucket *cpy;
+            apr_bucket_copy(b, &cpy);
+            APR_BRIGADE_INSERT_TAIL(bb_tmp, cpy);
+            break;
+        }
+
         rv = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
         if (rv != APR_SUCCESS) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01463) "apr_bucket_read()");
             return rv;
         }
 
