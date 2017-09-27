 
         ap_internal_redirect_handler(location, r);
         return OK;
     }
 
     if (!r->header_only) {
+        conn_rec *c = r->connection;
         apr_bucket_brigade *bb;
         apr_bucket *b;
         apr_off_t pos = 0;
 
         rv = apr_file_seek(f, APR_CUR, &pos);
         if (rv != APR_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01235)
                           "mod_asis: failed to find end-of-headers position "
                           "for %s", r->filename);
             apr_file_close(f);
             return HTTP_INTERNAL_SERVER_ERROR;
         }
 
