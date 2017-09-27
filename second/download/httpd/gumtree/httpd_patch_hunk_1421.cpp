         rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                             APR_BLOCK_READ, HUGE_STRING_LEN);
 
         if (rv != APR_SUCCESS) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                           "Error reading request entity data");
-            return HTTP_INTERNAL_SERVER_ERROR;
+            return ap_map_http_request_error(rv, HTTP_BAD_REQUEST);
         }
 
         for (bucket = APR_BRIGADE_FIRST(bb);
              bucket != APR_BRIGADE_SENTINEL(bb);
              bucket = APR_BUCKET_NEXT(bucket))
         {
