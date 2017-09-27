             return 1;
         }
         if (cid->dconf.log_unsupported)
             ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                       "ISAPI: ServerSupportFunction HSE_REQ_IO_COMPLETION "
                       "is not supported: %s", r->filename);
-        SetLastError(ERROR_INVALID_PARAMETER);
+        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
         return 0;
 
     case HSE_REQ_TRANSMIT_FILE:
     {
         /* we do nothing with (tf->dwFlags & HSE_DISCONNECT_AFTER_SEND)
          */
