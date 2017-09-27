             rv = apr_get_os_error();
             ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                          "Failed to open the WinNT service manager.");
             return (rv);
         }
 
-        /* ###: utf-ize */
-        schService = OpenService(schSCManager, mpm_service_name, DELETE);
-
+#if APR_HAS_UNICODE_FS
+        IF_WIN_OS_IS_UNICODE
+        {
+            schService = OpenServiceW(schSCManager, mpm_service_name_w, DELETE);
+        }
+#endif /* APR_HAS_UNICODE_FS */
+#if APR_HAS_ANSI_FS
+        ELSE_WIN_OS_IS_ANSI
+        {
+            schService = OpenService(schSCManager, mpm_service_name, DELETE);
+        }
+#endif
         if (!schService) {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "%s: OpenService failed", mpm_display_name);
            return (rv);
         }
