          */
         return 1;
     }
 
     case HSE_REQ_CLOSE_CONNECTION:  /* Added after ISAPI 4.0 */
         if (cid->dconf.log_unsupported)
-            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02679)
                           "ServerSupportFunction "
                           "HSE_REQ_CLOSE_CONNECTION "
                           "is not supported: %s", r->filename);
         apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
         return 0;
 
