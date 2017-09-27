 
     case HSE_REQ_MAP_URL_TO_PATH:
     {
         /* Map a URL to a filename */
         char *file = (char *)buf_data;
         apr_uint32_t len;
-        subreq = ap_sub_req_lookup_uri(apr_pstrndup(r->pool, file, *buf_size),
-                                       r, NULL);
+        subreq = ap_sub_req_lookup_uri(
+                     apr_pstrndup(cid->r->pool, file, *buf_size), r, NULL);
 
-        len = apr_cpystrn(file, subreq->filename, *buf_size) - file;
+        if (!subreq->filename) {
+            ap_destroy_sub_req(subreq);
+            return 0;
+        }
 
+        len = (apr_uint32_t)strlen(r->filename);
+
+        if ((subreq->finfo.filetype == APR_DIR)
+              && (!subreq->path_info)
+              && (file[len - 1] != '/'))
+            file = apr_pstrcat(cid->r->pool, subreq->filename, "/", NULL);
+        else
+            file = apr_pstrcat(cid->r->pool, subreq->filename, 
+                                              subreq->path_info, NULL);
+
+        ap_destroy_sub_req(subreq);
+
+#ifdef WIN32
+        /* We need to make this a real Windows path name */
+        apr_filepath_merge(&file, "", file, APR_FILEPATH_NATIVE, r->pool);
+#endif
+
+        *buf_size = apr_cpystrn(buf_data, file, *buf_size) - buf_data;
 
-        /* IIS puts a trailing slash on directories, Apache doesn't */
-        if (subreq->finfo.filetype == APR_DIR) {
-            if (len < *buf_size - 1) {
-                file[len++] = '\\';
-                file[len] = '\0';
-            }
-        }
-        *buf_size = len;
         return 1;
     }
 
     case HSE_REQ_GET_SSPI_INFO:
         if (cid->dconf.log_unsupported)
             ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                            "ISAPI: ServerSupportFunction HSE_REQ_GET_SSPI_INFO "
                            "is not supported: %s", r->filename);
         apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
         return 0;
-        
+
     case HSE_APPEND_LOG_PARAMETER:
         /* Log buf_data, of buf_size bytes, in the URI Query (cs-uri-query) field
          */
         apr_table_set(r->notes, "isapi-parameter", (char*) buf_data);
         if (cid->dconf.log_to_query) {
             if (r->args)
