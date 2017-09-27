         mpm_new_argv->nelts = mpm_new_argv->nalloc;
     }
 
     /* Let the main thread continue now... but hang on to the
      * signal_monitor event so we can take further action
      */
-    SetEvent(globdat.service_init);
+    SetEvent(ctx->service_init);
 
-    WaitForSingleObject(globdat.service_term, INFINITE);
+    WaitForSingleObject(ctx->service_term, INFINITE);
 }
-#endif
 
 
-static DWORD WINAPI service_nt_dispatch_thread(LPVOID nada)
+DWORD WINAPI service_nt_dispatch_thread(LPVOID nada)
 {
-#if APR_HAS_UNICODE_FS
-    SERVICE_TABLE_ENTRYW dispatchTable_w[] =
-    {
-        { L"", service_nt_main_fn_w },
-        { NULL, NULL }
-    };
-#endif /* APR_HAS_UNICODE_FS */
-#if APR_HAS_ANSI_FS
-    SERVICE_TABLE_ENTRYA dispatchTable[] =
+    apr_status_t rv = APR_SUCCESS;
+
+    SERVICE_TABLE_ENTRY dispatchTable[] =
     {
         { "", service_nt_main_fn },
         { NULL, NULL }
     };
-#endif
-    apr_status_t rv;
 
-#if APR_HAS_UNICODE_FS
-    IF_WIN_OS_IS_UNICODE
-        rv = StartServiceCtrlDispatcherW(dispatchTable_w);
-#endif
-#if APR_HAS_ANSI_FS
-    ELSE_WIN_OS_IS_ANSI
-         rv = StartServiceCtrlDispatcherA(dispatchTable);
-#endif
-    if (rv) {
-        apr_status_t rv = APR_SUCCESS;
-    }
-    else {
+    /* ###: utf-ize */
+    if (!StartServiceCtrlDispatcher(dispatchTable))
+    {
         /* This is a genuine failure of the SCM. */
         rv = apr_get_os_error();
         ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                      "Error starting service control dispatcher");
     }
+
     return (rv);
 }
 
 
+/* The service configuration's is stored under the following trees:
+ *
+ * HKLM\System\CurrentControlSet\Services\[service name]
+ *
+ *     \DisplayName
+ *     \ImagePath
+ *     \Parameters\ConfigArgs
+ */
+
+
 apr_status_t mpm_service_set_name(apr_pool_t *p, const char **display_name,
                                   const char *set_name)
 {
     char key_name[MAX_PATH];
     ap_regkey_t *key;
     apr_status_t rv;
