     struct accept_rec accept_info;
     void *new_var;
     int anymatch = 0;
 
     clean_var_rec(&mime_info);
 
-    if (r->proxyreq || !r->filename 
+    if (r->proxyreq || !r->filename
                     || !ap_os_is_path_absolute(neg->pool, r->filename)) {
         return DECLINED;
     }
 
     /* Only absolute paths here */
     if (!(filp = strrchr(r->filename, '/'))) {
         return DECLINED;
     }
     ++filp;
     prefix_len = strlen(filp);
 
-    if ((status = apr_dir_open(&dirp, neg->dir_name, neg->pool)) != APR_SUCCESS) {
+    if ((status = apr_dir_open(&dirp, neg->dir_name,
+                               neg->pool)) != APR_SUCCESS) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                     "cannot read directory for multi: %s", neg->dir_name);
         return HTTP_FORBIDDEN;
     }
 
     while (apr_dir_read(&dirent, APR_FINFO_DIRENT, dirp) == APR_SUCCESS) {
         apr_array_header_t *exception_list;
         request_rec *sub_req;
-        
+
         /* Do we have a match? */
 #ifdef CASE_BLIND_FILESYSTEM
         if (strncasecmp(dirent.name, filp, prefix_len)) {
 #else
         if (strncmp(dirent.name, filp, prefix_len)) {
 #endif
