         if (!dryrun) {
             const char *remove;
             apr_status_t status;
 
             remove = apr_pstrcat(pool, base, "/", header, NULL);
             status = apr_file_remove(remove, pool);
-            if (status != APR_SUCCESS && status != APR_ENOENT) {
+            if (status != APR_SUCCESS && !APR_STATUS_IS_ENOENT(status)) {
                 char errmsg[120];
                 apr_file_printf(errfile, "Could not remove file %s: %s" APR_EOL_STR,
                         remove, apr_strerror(status, errmsg, sizeof errmsg));
                 rv = status;
             }
 
             remove = apr_pstrcat(pool, base, "/", data, NULL);
             status = apr_file_remove(remove, pool);
-            if (status != APR_SUCCESS && status != APR_ENOENT) {
+            if (status != APR_SUCCESS && !APR_STATUS_IS_ENOENT(status)) {
                 char errmsg[120];
                 apr_file_printf(errfile, "Could not remove file %s: %s" APR_EOL_STR,
                         remove, apr_strerror(status, errmsg, sizeof errmsg));
                 rv = status;
             }
 
             status = remove_directory(pool, apr_pstrcat(pool, base, "/", vdir, NULL));
-            if (status != APR_SUCCESS && status != APR_ENOENT) {
+            if (status != APR_SUCCESS && !APR_STATUS_IS_ENOENT(status)) {
                 rv = status;
             }
         }
     }
 
     /* If asked to delete dirs, do so now. We don't care if it fails.
