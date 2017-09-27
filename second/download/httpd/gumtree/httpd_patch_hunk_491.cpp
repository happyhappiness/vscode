         else if (cid->dconf.log_unsupported) {
             ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                           "ISAPI: ServerSupportFunction "
                           "HSE_REQ_DONE_WITH_SESSION is not supported: %s",
                           r->filename);
         }
-        SetLastError(ERROR_INVALID_PARAMETER);
+        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
         return 0;
 
     case HSE_REQ_MAP_URL_TO_PATH:
     {
         /* Map a URL to a filename */
         char *file = (char *)buf_data;
