         const apr_pollfd_t *results;
         apr_int32_t num;
 
         rv = apr_pollset_poll(data->pollset, timeout, &num, &results);
         if (APR_STATUS_IS_TIMEUP(rv)) {
             if (timeout) {
-                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, data->r,
+                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, data->r, APLOGNO(01220)
                               "Timeout waiting for output from CGI script %s",
                               data->r->filename);
                 return rv;
             }
             else {
                 return APR_EAGAIN;
             }
         }
         else if (APR_STATUS_IS_EINTR(rv)) {
             continue;
         }
         else if (rv != APR_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, data->r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, data->r, APLOGNO(01221)
                           "poll failed waiting for CGI child");
             return rv;
         }
 
         for (; num; num--, results++) {
             if (results[0].client_data == (void *)1) {
