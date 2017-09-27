                                0, r->pool);
         filename_len = strlen(r->filename);
 
 #endif
 
         if (rv != APR_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00034)
                           "dir_walk error, could not determine the root "
                           "path of filename %s%s for uri %s",
                           r->filename, r->path_info, r->uri);
             return HTTP_INTERNAL_SERVER_ERROR;
         }
 
