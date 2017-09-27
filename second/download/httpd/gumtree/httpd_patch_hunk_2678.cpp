             eos = b;
             break;
         }
 
         rv = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
         if (rv != APR_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "apr_bucket_read()");
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01463) "apr_bucket_read()");
             return rv;
         }
 
         /* Good cast, we just tested len isn't negative */
         if (len > 0 &&
             (rv = pass_data_to_filter(f, data, (apr_size_t)len, bb_tmp))
