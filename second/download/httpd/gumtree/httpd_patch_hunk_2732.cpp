 
         rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                             APR_BLOCK_READ, HUGE_STRING_LEN);
 
         if (rv != APR_SUCCESS) {
             if (APR_STATUS_IS_TIMEUP(rv)) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01224)
                               "Timeout during reading request entity data");
                 return HTTP_REQUEST_TIME_OUT;
             }
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01225)
                           "Error reading request entity data");
             return HTTP_INTERNAL_SERVER_ERROR;
         }
 
         for (bucket = APR_BRIGADE_FIRST(bb);
              bucket != APR_BRIGADE_SENTINEL(bb);
