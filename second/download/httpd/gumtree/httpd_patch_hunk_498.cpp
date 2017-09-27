 
     case HSE_REQ_ABORTIVE_CLOSE:
         if (cid->dconf.log_unsupported)
             ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                           "ISAPI: ServerSupportFunction HSE_REQ_ABORTIVE_CLOSE"
                           " is not supported: %s", r->filename);
-        SetLastError(ERROR_INVALID_PARAMETER);
+        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
         return 0;
 
     case HSE_REQ_GET_CERT_INFO_EX:  /* Added in ISAPI 4.0 */
         if (cid->dconf.log_unsupported)
             ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                           "ISAPI: ServerSupportFunction "
                           "HSE_REQ_GET_CERT_INFO_EX "
                           "is not supported: %s", r->filename);        
-        SetLastError(ERROR_INVALID_PARAMETER);
+        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
         return 0;
 
     case HSE_REQ_SEND_RESPONSE_HEADER_EX:  /* Added in ISAPI 4.0 */
     {
         HSE_SEND_HEADER_EX_INFO *shi = (HSE_SEND_HEADER_EX_INFO*)buf_data;
 
