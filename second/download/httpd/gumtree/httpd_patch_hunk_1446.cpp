 /* service_nt_main_fn is outside of the call stack and outside of the
  * primary server thread... so now we _really_ need a placeholder!
  * The winnt_rewrite_args has created and shared mpm_new_argv with us.
  */
 extern apr_array_header_t *mpm_new_argv;
 
-/* ###: utf-ize */
-static void __stdcall service_nt_main_fn(DWORD argc, LPTSTR *argv)
+#if APR_HAS_UNICODE_FS
+static void __stdcall service_nt_main_fn_w(DWORD argc, LPWSTR *argv)
+{
+    const char *ignored;
+    char *service_name;
+    apr_size_t wslen = wcslen(argv[0]) + 1;
+    apr_size_t slen = wslen * 3 - 2;
+
+    service_name = malloc(slen);
+    (void)apr_conv_ucs2_to_utf8(argv[0], &wslen, service_name, &slen);
+
+    /* args and service names live in the same pool */
+    mpm_service_set_name(mpm_new_argv->pool, &ignored, service_name);
+
+    memset(&globdat.ssStatus, 0, sizeof(globdat.ssStatus));
+    globdat.ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
+    globdat.ssStatus.dwCurrentState = SERVICE_START_PENDING;
+    globdat.ssStatus.dwCheckPoint = 1;
+
+    if (!(globdat.hServiceStatus = RegisterServiceCtrlHandlerW(argv[0], service_nt_ctrl)))
+    {
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
+                     NULL, "Failure registering service handler");
+        return;
+    }
+
+    /* Report status, no errors, and buy 3 more seconds */
+    ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 30000);
+
+    /* We need to append all the command arguments passed via StartService()
+     * to our running service... which just got here via the SCM...
+     * but we have no interest in argv[0] for the mpm_new_argv list.
+     */
+    if (argc > 1)
+    {
+        char **cmb_data, **cmb;
+        DWORD i;
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
+        /* The replacement arg list is complete */
+        mpm_new_argv->elts = (char *)cmb_data;
+        mpm_new_argv->nelts = mpm_new_argv->nalloc;
+    }
+
+    /* Let the main thread continue now... but hang on to the
+     * signal_monitor event so we can take further action
+     */
+    SetEvent(globdat.service_init);
+
+    WaitForSingleObject(globdat.service_term, INFINITE);
+}
+#endif /* APR_HAS_UNICODE_FS */
+
+
+#if APR_HAS_ANSI_FS
+static void __stdcall service_nt_main_fn(DWORD argc, LPSTR *argv)
 {
     const char *ignored;
 
     /* args and service names live in the same pool */
     mpm_service_set_name(mpm_new_argv->pool, &ignored, argv[0]);
 
     memset(&globdat.ssStatus, 0, sizeof(globdat.ssStatus));
     globdat.ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
     globdat.ssStatus.dwCurrentState = SERVICE_START_PENDING;
     globdat.ssStatus.dwCheckPoint = 1;
 
-    /* ###: utf-ize */
-    if (!(globdat.hServiceStatus = RegisterServiceCtrlHandler(argv[0], service_nt_ctrl)))
+    if (!(globdat.hServiceStatus = RegisterServiceCtrlHandlerA(argv[0], service_nt_ctrl)))
     {
         ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
                      NULL, "Failure registering service handler");
         return;
     }
 
     /* Report status, no errors, and buy 3 more seconds */
     ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 30000);
 
     /* We need to append all the command arguments passed via StartService()
      * to our running service... which just got here via the SCM...
-     * but we hvae no interest in argv[0] for the mpm_new_argv list.
+     * but we have no interest in argv[0] for the mpm_new_argv list.
      */
     if (argc > 1)
     {
         char **cmb_data;
 
         mpm_new_argv->nalloc = mpm_new_argv->nelts + argc - 1;
