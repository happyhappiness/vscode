      * signal_monitor event so we can take further action
      */
     SetEvent(globdat.service_init);
 
     WaitForSingleObject(globdat.service_term, INFINITE);
 }
+#endif
 
 
 static DWORD WINAPI service_nt_dispatch_thread(LPVOID nada)
 {
-    apr_status_t rv = APR_SUCCESS;
-
-    SERVICE_TABLE_ENTRY dispatchTable[] =
+#if APR_HAS_UNICODE_FS
+    SERVICE_TABLE_ENTRYW dispatchTable_w[] =
+    {
+        { L"", service_nt_main_fn_w },
+        { NULL, NULL }
+    };
+#endif /* APR_HAS_UNICODE_FS */
+#if APR_HAS_ANSI_FS
+    SERVICE_TABLE_ENTRYA dispatchTable[] =
     {
         { "", service_nt_main_fn },
         { NULL, NULL }
     };
+#endif
+    apr_status_t rv;
 
-    /* ###: utf-ize */
-    if (!StartServiceCtrlDispatcher(dispatchTable))
-    {
+#if APR_HAS_UNICODE_FS
+    IF_WIN_OS_IS_UNICODE
+        rv = StartServiceCtrlDispatcherW(dispatchTable_w);
+#endif
+#if APR_HAS_ANSI_FS
+    ELSE_WIN_OS_IS_ANSI
+         rv = StartServiceCtrlDispatcherA(dispatchTable);
+#endif
+    if (rv) {
+        apr_status_t rv = APR_SUCCESS;
+    }
+    else {
         /* This is a genuine failure of the SCM. */
         rv = apr_get_os_error();
         ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                      "Error starting service control dispatcher");
     }
-
     return (rv);
 }
 
 
 apr_status_t mpm_service_set_name(apr_pool_t *p, const char **display_name,
                                   const char *set_name)
