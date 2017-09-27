     neg->count_multiviews_variants = 0;
 
     if ((status = apr_file_open(map, rr->filename, APR_READ | APR_BUFFERED,
                 APR_OS_DEFAULT, neg->pool)) != APR_SUCCESS) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                       "cannot access type map file: %s", rr->filename);
-        return HTTP_FORBIDDEN;
+        if (APR_STATUS_IS_ENOTDIR(status) || APR_STATUS_IS_ENOENT(status)) {
+            return HTTP_NOT_FOUND;
+        }
+        else {
+            return HTTP_FORBIDDEN;
+        }
     }
 
     clean_var_rec(&mime_info);
     has_content = 0;
 
     do {
