 
         CloseServiceHandle(schService);
         CloseServiceHandle(schSCManager);
     }
     else /* osver.dwPlatformId != VER_PLATFORM_WIN32_NT */
     {
+        char exe_path[MAX_PATH];
+
+        if (GetModuleFileName(NULL, exe_path, sizeof(exe_path)) == 0)
+        {
+            apr_status_t rv = apr_get_os_error();
+            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+                         "GetModuleFileName failed");
+            return rv;
+        }
+
         /* Store the launch command in the registry */
         launch_cmd = apr_psprintf(ptemp, "\"%s\" -n %s -k runservice",
                                  exe_path, mpm_service_name);
         rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, SERVICECONFIG9X,
                             APR_READ | APR_WRITE | APR_CREATE, pconf);
         if (rv == APR_SUCCESS) {
