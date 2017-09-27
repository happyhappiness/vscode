 
     /* We are not using multiviews */
     neg->count_multiviews_variants = 0;
 
     if ((status = apr_file_open(map, rr->filename, APR_READ | APR_BUFFERED,
                 APR_OS_DEFAULT, neg->pool)) != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00683)
                       "cannot access type map file: %s", rr->filename);
         if (APR_STATUS_IS_ENOTDIR(status) || APR_STATUS_IS_ENOENT(status)) {
             return HTTP_NOT_FOUND;
         }
         else {
             return HTTP_FORBIDDEN;
