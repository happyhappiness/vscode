 }
 
 
 apr_status_t mpm_service_started(void)
 {
     set_service_description();
-    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
-    {
-        ReportStatusToSCMgr(SERVICE_RUNNING,    // service state
-                            NO_ERROR,           // exit code
-                            0);                 // wait hint
-    }
+    ReportStatusToSCMgr(SERVICE_RUNNING, 0, &globdat);
     return APR_SUCCESS;
 }
 
 
 void mpm_service_stopping(void)
 {
-    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
-        ReportStatusToSCMgr(SERVICE_STOP_PENDING, // service state
-                            NO_ERROR,             // exit code
-                            30000);               // wait hint
+    ReportStatusToSCMgr(SERVICE_STOP_PENDING, 30000, &globdat);
 }
 
 
 apr_status_t mpm_service_install(apr_pool_t *ptemp, int argc,
                                  const char * const * argv, int reconfig)
 {
     char key_name[MAX_PATH];
+    char exe_path[MAX_PATH];
+    char *launch_cmd;
     ap_regkey_t *key;
-    char        *launch_cmd;
     apr_status_t rv;
+    SC_HANDLE   schService;
+    SC_HANDLE   schSCManager;
 
     fprintf(stderr,reconfig ? "Reconfiguring the %s service\n"
                    : "Installing the %s service\n", mpm_display_name);
 
-    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
+    /* ###: utf-ize */
+    if (GetModuleFileName(NULL, exe_path, sizeof(exe_path)) == 0)
     {
-        SC_HANDLE   schService;
-        SC_HANDLE   schSCManager;
-        DWORD       rc;
-#if APR_HAS_UNICODE_FS
-        apr_wchar_t *display_name_w;
-        apr_wchar_t *launch_cmd_w;
+        apr_status_t rv = apr_get_os_error();
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+                     "GetModuleFileName failed");
+        return rv;
+    }
 
-        IF_WIN_OS_IS_UNICODE
-        {
-            apr_size_t slen = strlen(mpm_display_name) + 1;
-            apr_size_t wslen = slen;
-            display_name_w = apr_palloc(ptemp, wslen * sizeof(apr_wchar_t));
-            rv = apr_conv_utf8_to_ucs2(mpm_display_name, &slen,
-                                       display_name_w, &wslen);
-            if (rv != APR_SUCCESS)
-                return rv;
-            else if (slen)
-                return APR_ENAMETOOLONG;
-
-            launch_cmd_w = apr_palloc(ptemp, (MAX_PATH + 17) * sizeof(apr_wchar_t));
-            launch_cmd_w[0] = L'"';
-            rc = GetModuleFileNameW(NULL, launch_cmd_w + 1, MAX_PATH);
-            wcscpy(launch_cmd_w + rc + 1, L"\" -k runservice");
-        }
-#endif /* APR_HAS_UNICODE_FS */
-#if APR_HAS_ANSI_FS
-        ELSE_WIN_OS_IS_ANSI
-        {
-            launch_cmd = apr_palloc(ptemp, MAX_PATH + 17);
-            launch_cmd[0] = '"';
-            rc = GetModuleFileName(NULL, launch_cmd + 1, MAX_PATH);
-            strcpy(launch_cmd + rc + 1, "\" -k runservice");
-        }
-#endif
-        if (rc == 0) {
-            rv = apr_get_os_error();
-            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
-                         "GetModuleFileName failed");
-            return rv;
-        }
+    schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
+                                 SC_MANAGER_CREATE_SERVICE);
+    if (!schSCManager) {
+        rv = apr_get_os_error();
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+                     "Failed to open the WinNT service manager, perhaps "
+                     "you forgot to log in as Adminstrator?");
+        return (rv);
+    }
 
-        schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
-                                     SC_MANAGER_CREATE_SERVICE);
-        if (!schSCManager) {
-            rv = apr_get_os_error();
-            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
-                         "Failed to open the WinNT service manager");
-            return (rv);
-        }
+    launch_cmd = apr_psprintf(ptemp, "\"%s\" -k runservice", exe_path);
 
-        if (reconfig) {
-#if APR_HAS_UNICODE_FS
-            IF_WIN_OS_IS_UNICODE
-            {
-                schService = OpenServiceW(schSCManager, mpm_service_name_w,
-                                      SERVICE_CHANGE_CONFIG);
-            }
-#endif /* APR_HAS_UNICODE_FS */
-#if APR_HAS_ANSI_FS
-            ELSE_WIN_OS_IS_ANSI
-            {
-                schService = OpenService(schSCManager, mpm_service_name,
-                                         SERVICE_CHANGE_CONFIG);
-            }
-#endif
-            if (!schService) {
-                ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_ERR,
-                             apr_get_os_error(), NULL,
-                             "OpenService failed");
-            }
-            else {
-#if APR_HAS_UNICODE_FS
-                IF_WIN_OS_IS_UNICODE
-                {
-                    rc = ChangeServiceConfigW(schService,
-                                              SERVICE_WIN32_OWN_PROCESS,
-                                              SERVICE_AUTO_START,
-                                              SERVICE_ERROR_NORMAL,
-                                              launch_cmd_w, NULL, NULL,
-                                              L"Tcpip\0Afd\0", NULL, NULL,
-                                              display_name_w);
-                }
-#endif /* APR_HAS_UNICODE_FS */
-#if APR_HAS_ANSI_FS
-                ELSE_WIN_OS_IS_ANSI
-                {
-                    rc = ChangeServiceConfig(schService,
-                                             SERVICE_WIN32_OWN_PROCESS,
-                                             SERVICE_AUTO_START,
-                                             SERVICE_ERROR_NORMAL,
-                                             launch_cmd, NULL, NULL,
-                                             "Tcpip\0Afd\0", NULL, NULL,
-                                             mpm_display_name);
-                }
-#endif
-                if (!rc) {
-                    ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_ERR,
-                                 apr_get_os_error(), NULL,
-                                 "ChangeServiceConfig failed");
-                    /* !schService aborts configuration below */
-                    CloseServiceHandle(schService);
-                    schService = NULL;
-                }
-            }
-        }
-        else {
-            /* RPCSS is the Remote Procedure Call (RPC) Locator required
-             * for DCOM communication pipes.  I am far from convinced we
-             * should add this to the default service dependencies, but
-             * be warned that future apache modules or ISAPI dll's may
-             * depend on it.
-             */
+    if (reconfig) {
+        /* ###: utf-ize */
+        schService = OpenService(schSCManager, mpm_service_name,
+                                 SERVICE_CHANGE_CONFIG);
+        if (!schService) {
+            ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_ERR,
+                         apr_get_os_error(), NULL,
+                         "OpenService failed");
+        }
+        /* ###: utf-ize */
+        else if (!ChangeServiceConfig(schService,
+                                      SERVICE_WIN32_OWN_PROCESS,
+                                      SERVICE_AUTO_START,
+                                      SERVICE_ERROR_NORMAL,
+                                      launch_cmd, NULL, NULL,
+                                      "Tcpip\0Afd\0", NULL, NULL,
+                                      mpm_display_name)) {
+            ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_ERR,
+                         apr_get_os_error(), NULL,
+                         "ChangeServiceConfig failed");
 
-#if APR_HAS_UNICODE_FS
-            IF_WIN_OS_IS_UNICODE
-            {
-                schService = CreateServiceW(schSCManager,    // SCManager database
-                                 mpm_service_name_w,   // name of service
-                                 display_name_w,   // name to display
-                                 SERVICE_ALL_ACCESS,   // access required
-                                 SERVICE_WIN32_OWN_PROCESS,  // service type
-                                 SERVICE_AUTO_START,   // start type
-                                 SERVICE_ERROR_NORMAL, // error control type
-                                 launch_cmd_w,         // service's binary
-                                 NULL,                 // no load svc group
-                                 NULL,                 // no tag identifier
-                                 L"Tcpip\0Afd\0",      // dependencies
-                                 NULL,                 // use SYSTEM account
-                                 NULL);                // no password
-            }
-#endif /* APR_HAS_UNICODE_FS */
-#if APR_HAS_ANSI_FS
-            ELSE_WIN_OS_IS_ANSI
-            {
-                schService = CreateService(schSCManager,     // SCManager database
-                                 mpm_service_name,     // name of service
-                                 mpm_display_name,     // name to display
-                                 SERVICE_ALL_ACCESS,   // access required
-                                 SERVICE_WIN32_OWN_PROCESS,  // service type
-                                 SERVICE_AUTO_START,   // start type
-                                 SERVICE_ERROR_NORMAL, // error control type
-                                 launch_cmd,           // service's binary
-                                 NULL,                 // no load svc group
-                                 NULL,                 // no tag identifier
-                                 "Tcpip\0Afd\0",       // dependencies
-                                 NULL,                 // use SYSTEM account
-                                 NULL);                // no password
-            }
-#endif
-            if (!schService)
-            {
-                rv = apr_get_os_error();
-                ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
-                             "Failed to create WinNT Service Profile");
-                CloseServiceHandle(schSCManager);
-                return (rv);
+            /* !schService aborts configuration below */
+            CloseServiceHandle(schService);
+            schService = NULL;
             }
         }
+    else {
+        /* RPCSS is the Remote Procedure Call (RPC) Locator required
+         * for DCOM communication pipes.  I am far from convinced we
+         * should add this to the default service dependencies, but
+         * be warned that future apache modules or ISAPI dll's may
+         * depend on it.
+         */
+        /* ###: utf-ize */
+        schService = CreateService(schSCManager,         // SCManager database
+                                   mpm_service_name,     // name of service
+                                   mpm_display_name,     // name to display
+                                   SERVICE_ALL_ACCESS,   // access required
+                                   SERVICE_WIN32_OWN_PROCESS,  // service type
+                                   SERVICE_AUTO_START,   // start type
+                                   SERVICE_ERROR_NORMAL, // error control type
+                                   launch_cmd,           // service's binary
+                                   NULL,                 // no load svc group
+                                   NULL,                 // no tag identifier
+                                   "Tcpip\0Afd\0",       // dependencies
+                                   NULL,                 // use SYSTEM account
+                                   NULL);                // no password
 
-        CloseServiceHandle(schService);
-        CloseServiceHandle(schSCManager);
-    }
-    else /* osver.dwPlatformId != VER_PLATFORM_WIN32_NT */
-    {
-        char exe_path[MAX_PATH];
-
-        if (GetModuleFileName(NULL, exe_path, sizeof(exe_path)) == 0)
+        if (!schService)
         {
-            apr_status_t rv = apr_get_os_error();
-            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
-                         "GetModuleFileName failed");
-            return rv;
-        }
-
-        /* Store the launch command in the registry */
-        launch_cmd = apr_psprintf(ptemp, "\"%s\" -n %s -k runservice",
-                                 exe_path, mpm_service_name);
-        rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, SERVICECONFIG9X,
-                            APR_READ | APR_WRITE | APR_CREATE, pconf);
-        if (rv == APR_SUCCESS) {
-            rv = ap_regkey_value_set(key, mpm_service_name,
-                                     launch_cmd, 0, pconf);
-            ap_regkey_close(key);
-        }
-        if (rv != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
-                         "%s: Failed to add the RunServices registry entry.",
-                         mpm_display_name);
-            return (rv);
-        }
-
-        apr_snprintf(key_name, sizeof(key_name), SERVICECONFIG, mpm_service_name);
-        rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, key_name,
-                            APR_READ | APR_WRITE | APR_CREATE, pconf);
-        if (rv != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
-                         "%s: Failed to create the registry service key.",
-                         mpm_display_name);
-            return (rv);
-        }
-        rv = ap_regkey_value_set(key, "ImagePath", launch_cmd, 0, pconf);
-        if (rv != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
-                         "%s: Failed to store ImagePath in the registry.",
-                         mpm_display_name);
-            ap_regkey_close(key);
-            return (rv);
-        }
-        rv = ap_regkey_value_set(key, "DisplayName",
-                                 mpm_display_name, 0, pconf);
-        ap_regkey_close(key);
-        if (rv != APR_SUCCESS) {
+            rv = apr_get_os_error();
             ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
-                         "%s: Failed to store DisplayName in the registry.",
-                         mpm_display_name);
+                         "Failed to create WinNT Service Profile");
+            CloseServiceHandle(schSCManager);
             return (rv);
         }
     }
 
+    CloseServiceHandle(schService);
+    CloseServiceHandle(schSCManager);
+
     set_service_description();
 
-    /* For both WinNT & Win9x store the service ConfigArgs in the registry...
+    /* Store the service ConfigArgs in the registry...
      */
     apr_snprintf(key_name, sizeof(key_name), SERVICEPARAMS, mpm_service_name);
     rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, key_name,
                         APR_READ | APR_WRITE | APR_CREATE, pconf);
     if (rv == APR_SUCCESS) {
         rv = ap_regkey_value_array_set(key, "ConfigArgs", argc, argv, pconf);
