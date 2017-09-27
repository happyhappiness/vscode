     if ((errstatus = ap_discard_request_body(r)) != OK) {
         return errstatus;
     }
 
     if (r->method_number == M_GET || r->method_number == M_POST) {
         if (r->finfo.filetype == APR_NOFILE) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00128)
                           "File does not exist: %s", r->filename);
             return HTTP_NOT_FOUND;
         }
 
         /* Don't try to serve a dir.  Some OSs do weird things with
          * raw I/O on a dir.
          */
         if (r->finfo.filetype == APR_DIR) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00129)
                           "Attempt to serve directory: %s", r->filename);
             return HTTP_NOT_FOUND;
         }
 
         if ((r->used_path_info != AP_REQ_ACCEPT_PATH_INFO) &&
             r->path_info && *r->path_info)
         {
             /* default to reject */
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00130)
                           "File does not exist: %s",
                           apr_pstrcat(r->pool, r->filename, r->path_info, NULL));
             return HTTP_NOT_FOUND;
         }
 
         /* We understood the (non-GET) method, but it might not be legal for
