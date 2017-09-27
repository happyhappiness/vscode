 /* service_nt_main_fn is outside of the call stack and outside of the
  * primary server thread... so now we _really_ need a placeholder!
  * The winnt_rewrite_args has created and shared mpm_new_argv with us.
  */
 extern apr_array_header_t *mpm_new_argv;
 
-/* ###: utf-ize */
-static void __stdcall service_nt_main_fn(DWORD argc, LPTSTR *argv)
+#if APR_HAS_UNICODE_FS
+static void __stdcall service_nt_main_fn_w(DWORD argc, LPWSTR *argv)
 {
     const char *ignored;
     nt_service_ctx_t *ctx = &globdat;
+    char *service_name;
+    apr_size_t wslen = wcslen(argv[0]) + 1;
+    apr_size_t slen = wslen * 3 - 2;
+
+    service_name = malloc(slen);
+    (void)apr_conv_ucs2_to_utf8(argv[0], &wslen, service_name, &slen);
 
     /* args and service names live in the same pool */
-    mpm_service_set_name(mpm_new_argv->pool, &ignored, argv[0]);
+    mpm_service_set_name(mpm_new_argv->pool, &ignored, service_name);
 
     memset(&ctx->ssStatus, 0, sizeof(ctx->ssStatus));
     ctx->ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
     ctx->ssStatus.dwCurrentState = SERVICE_START_PENDING;
     ctx->ssStatus.dwCheckPoint = 1;
-
-    /* ###: utf-ize */
-    if (!(ctx->hServiceStatus = RegisterServiceCtrlHandlerEx(argv[0], service_nt_ctrl, ctx)))
+    if (!(ctx->hServiceStatus = 
+              RegisterServiceCtrlHandlerExW(argv[0], service_nt_ctrl, ctx)))
     {
-        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
-                     NULL, APLOGNO(00365) "Failure registering service handler");
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, 
+                     apr_get_os_error(), NULL, 
+                     APLOGNO(00365) "Failure registering service handler");
         return;
     }
 
     /* Report status, no errors, and buy 3 more seconds */
     ReportStatusToSCMgr(SERVICE_START_PENDING, 30000, ctx);
 
     /* We need to append all the command arguments passed via StartService()
      * to our running service... which just got here via the SCM...
-     * but we hvae no interest in argv[0] for the mpm_new_argv list.
+     * but we have no interest in argv[0] for the mpm_new_argv list.
      */
     if (argc > 1)
     {
-        char **cmb_data;
+        char **cmb_data, **cmb;
+        DWORD i;
 
         mpm_new_argv->nalloc = mpm_new_argv->nelts + argc - 1;
         cmb_data = malloc(mpm_new_argv->nalloc * sizeof(const char *));
 
         /* mpm_new_argv remains first (of lower significance) */
         memcpy (cmb_data, mpm_new_argv->elts,
                 mpm_new_argv->elt_size * mpm_new_argv->nelts);
 
         /* Service args follow from StartService() invocation */
         memcpy (cmb_data + mpm_new_argv->nelts, argv + 1,
                 mpm_new_argv->elt_size * (argc - 1));
 
+        cmb = cmb_data + mpm_new_argv->nelts;
+
+        for (i = 1; i < argc; ++i)
+        {
+            wslen = wcslen(argv[i]) + 1;
+            slen = wslen * 3 - 2;
+            service_name = malloc(slen);
+            (void)apr_conv_ucs2_to_utf8(argv[i], &wslen, *(cmb++), &slen);
+        }
+
         /* The replacement arg list is complete */
         mpm_new_argv->elts = (char *)cmb_data;
         mpm_new_argv->nelts = mpm_new_argv->nalloc;
     }
 
     /* Let the main thread continue now... but hang on to the
      * signal_monitor event so we can take further action
      */
     SetEvent(ctx->service_init);
 
     WaitForSingleObject(ctx->service_term, INFINITE);
 }
+#endif /* APR_HAS_UNICODE_FS */
 
 
-static DWORD WINAPI service_nt_dispatch_thread(LPVOID nada)
+#if APR_HAS_ANSI_FS
+static void __stdcall service_nt_main_fn(DWORD argc, LPSTR *argv)
 {
-    apr_status_t rv = APR_SUCCESS;
+    const char *ignored;
+    nt_service_ctx_t *ctx = &globdat;
+
+    /* args and service names live in the same pool */
+    mpm_service_set_name(mpm_new_argv->pool, &ignored, argv[0]);
+
+    memset(&ctx->ssStatus, 0, sizeof(ctx->ssStatus));
+    ctx->ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
+    ctx->ssStatus.dwCurrentState = SERVICE_START_PENDING;
+    ctx->ssStatus.dwCheckPoint = 1;
 
-    SERVICE_TABLE_ENTRY dispatchTable[] =
+    if (!(ctx->hServiceStatus = 
+              RegisterServiceCtrlHandlerExA(argv[0], service_nt_ctrl, ctx)))
+        {
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, 
+                     apr_get_os_error(), NULL, 
+                     APLOGNO(00365) "Failure registering service handler");
+        return;
+    }
+
+    /* Report status, no errors, and buy 3 more seconds */
+    ReportStatusToSCMgr(SERVICE_START_PENDING, 30000, ctx);
+
+    /* We need to append all the command arguments passed via StartService()
+     * to our running service... which just got here via the SCM...
+     * but we have no interest in argv[0] for the mpm_new_argv list.
+     */
+    if (argc > 1)
     {
-        { "", service_nt_main_fn },
+        char **cmb_data;
+
+        mpm_new_argv->nalloc = mpm_new_argv->nelts + argc - 1;
+        cmb_data = malloc(mpm_new_argv->nalloc * sizeof(const char *));
+
+        /* mpm_new_argv remains first (of lower significance) */
+        memcpy (cmb_data, mpm_new_argv->elts,
+                mpm_new_argv->elt_size * mpm_new_argv->nelts);
+
+        /* Service args follow from StartService() invocation */
+        memcpy (cmb_data + mpm_new_argv->nelts, argv + 1,
+                mpm_new_argv->elt_size * (argc - 1));
+
+        /* The replacement arg list is complete */
+        mpm_new_argv->elts = (char *)cmb_data;
+        mpm_new_argv->nelts = mpm_new_argv->nalloc;
+    }
+
+    /* Let the main thread continue now... but hang on to the
+     * signal_monitor event so we can take further action
+     */
+    SetEvent(ctx->service_init);
+
+    WaitForSingleObject(ctx->service_term, INFINITE);
+}
+#endif
+
+
+ static DWORD WINAPI service_nt_dispatch_thread(LPVOID nada)
+ {
+#if APR_HAS_UNICODE_FS
+    SERVICE_TABLE_ENTRYW dispatchTable_w[] =
+    {
+        { L"", service_nt_main_fn_w },
         { NULL, NULL }
     };
-
-    /* ###: utf-ize */
-    if (!StartServiceCtrlDispatcher(dispatchTable))
+#endif /* APR_HAS_UNICODE_FS */
+#if APR_HAS_ANSI_FS
+    SERVICE_TABLE_ENTRYA dispatchTable[] =
     {
+        { "", service_nt_main_fn },
+        { NULL, NULL }
+    };
+#endif
+    apr_status_t rv;
+ 
+#if APR_HAS_UNICODE_FS
+    IF_WIN_OS_IS_UNICODE
+        rv = StartServiceCtrlDispatcherW(dispatchTable_w);
+#endif
+#if APR_HAS_ANSI_FS
+    ELSE_WIN_OS_IS_ANSI
+         rv = StartServiceCtrlDispatcherA(dispatchTable);
+#endif
+    if (rv) {
+        rv = APR_SUCCESS;
+    }
+    else {
         /* This is a genuine failure of the SCM. */
         rv = apr_get_os_error();
-        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, APLOGNO(00366)
-                     "Error starting service control dispatcher");
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+                     APLOGNO(00366) "Error starting Windows service control "
+                     "dispatcher");
     }
-
     return (rv);
 }
 
 
 /* The service configuration's is stored under the following trees:
  *
