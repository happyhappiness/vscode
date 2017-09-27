      * modules to proceed, we will permit the not-a-path filename to pass the
      * following two tests.  This behavior may be revoked in future versions
      * of Apache.  We still must catch it later if it's heading for the core
      * handler.  Leave INFO notes here for module debugging.
      */
     if (r->filename == NULL) {
-        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00029)
                       "Module bug?  Request filename is missing for URI %s",
                       r->uri);
        return OK;
     }
 
     /* Canonicalize the file path without resolving filename case or aliases
      * so we can begin by checking the cache for a recent directory walk.
      * This call will ensure we have an absolute path in the same pass.
      */
     if ((rv = apr_filepath_merge(&entry_dir, NULL, r->filename,
                                  APR_FILEPATH_NOTRELATIVE, r->pool))
                   != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00030)
                       "Module bug?  Request filename path %s is invalid or "
                       "or not absolute for uri %s",
                       r->filename, r->uri);
         return OK;
     }
 
