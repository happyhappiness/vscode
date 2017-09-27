         int res;
         if (!cid->dconf.fake_async) {
             if (cid->dconf.log_unsupported)
                 ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                             "ISAPI: asynchronous I/O not supported: %s",
                             r->filename);
-            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
+            SetLastError(ERROR_INVALID_PARAMETER);
             return 0;
         }
 
         if (r->remaining < *buf_size) {
             *buf_size = (apr_size_t)r->remaining;
         }
