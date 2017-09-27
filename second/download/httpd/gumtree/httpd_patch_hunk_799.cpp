                             APR_BLOCK_READ, 8192);
         if (rv) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                           "could not read request body for SSL buffer");
             return HTTP_INTERNAL_SERVER_ERROR;
         }
-        
+
         /* Iterate through the returned brigade: setaside each bucket
          * into the context's pool and move it into the brigade. */
-        for (e = APR_BRIGADE_FIRST(tempb); 
+        for (e = APR_BRIGADE_FIRST(tempb);
              e != APR_BRIGADE_SENTINEL(tempb) && !eos; e = next) {
             const char *data;
             apr_size_t len;
 
             next = APR_BUCKET_NEXT(e);
 
