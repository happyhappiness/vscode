 
     rv = apr_dir_open(&dirp, dir, pool);
     if (APR_STATUS_IS_ENOENT(rv)) {
         return rv;
     }
     if (rv != APR_SUCCESS) {
-        char errmsg[120];
-        apr_file_printf(errfile, "Could not open directory %s: %s" APR_EOL_STR,
-                dir, apr_strerror(rv, errmsg, sizeof errmsg));
+        apr_file_printf(errfile, "Could not open directory %s: %pm" APR_EOL_STR,
+                dir, &rv);
         return rv;
     }
 
     while (apr_dir_read(&dirent, APR_FINFO_DIRENT | APR_FINFO_TYPE, dirp)
             == APR_SUCCESS) {
         if (dirent.filetype == APR_DIR) {
