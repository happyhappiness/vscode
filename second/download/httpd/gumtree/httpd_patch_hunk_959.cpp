                                    NULL,                 // no load svc group
                                    NULL,                 // no tag identifier
                                    "Tcpip\0Afd\0",       // dependencies
                                    NULL,                 // use SYSTEM account
                                    NULL);                // no password
 
-            if (!schService) 
+            if (!schService)
             {
                 rv = apr_get_os_error();
-                ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
+                ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                              "Failed to create WinNT Service Profile");
                 CloseServiceHandle(schSCManager);
                 return (rv);
             }
         }
-	
+
         CloseServiceHandle(schService);
         CloseServiceHandle(schSCManager);
     }
     else /* osver.dwPlatformId != VER_PLATFORM_WIN32_NT */
     {
         /* Store the launch command in the registry */
-        launch_cmd = apr_psprintf(ptemp, "\"%s\" -n %s -k runservice", 
+        launch_cmd = apr_psprintf(ptemp, "\"%s\" -n %s -k runservice",
                                  exe_path, mpm_service_name);
-        rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, SERVICECONFIG9X, 
+        rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, SERVICECONFIG9X,
                             APR_READ | APR_WRITE | APR_CREATE, pconf);
         if (rv == APR_SUCCESS) {
-            rv = ap_regkey_value_set(key, mpm_service_name, 
+            rv = ap_regkey_value_set(key, mpm_service_name,
                                      launch_cmd, 0, pconf);
             ap_regkey_close(key);
         }
         if (rv != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
-                         "%s: Failed to add the RunServices registry entry.", 
+            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+                         "%s: Failed to add the RunServices registry entry.",
                          mpm_display_name);
             return (rv);
         }
 
         apr_snprintf(key_name, sizeof(key_name), SERVICECONFIG, mpm_service_name);
-        rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, key_name, 
+        rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, key_name,
                             APR_READ | APR_WRITE | APR_CREATE, pconf);
         if (rv != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
-                         "%s: Failed to create the registry service key.", 
+            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+                         "%s: Failed to create the registry service key.",
                          mpm_display_name);
             return (rv);
         }
         rv = ap_regkey_value_set(key, "ImagePath", launch_cmd, 0, pconf);
         if (rv != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
-                         "%s: Failed to store ImagePath in the registry.", 
+            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+                         "%s: Failed to store ImagePath in the registry.",
                          mpm_display_name);
             ap_regkey_close(key);
             return (rv);
         }
-        rv = ap_regkey_value_set(key, "DisplayName", 
+        rv = ap_regkey_value_set(key, "DisplayName",
                                  mpm_display_name, 0, pconf);
         ap_regkey_close(key);
         if (rv != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
-                         "%s: Failed to store DisplayName in the registry.", 
+            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+                         "%s: Failed to store DisplayName in the registry.",
                          mpm_display_name);
             return (rv);
         }
     }
 
     set_service_description();
 
     /* For both WinNT & Win9x store the service ConfigArgs in the registry...
      */
     apr_snprintf(key_name, sizeof(key_name), SERVICEPARAMS, mpm_service_name);
-    rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, key_name, 
+    rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, key_name,
                         APR_READ | APR_WRITE | APR_CREATE, pconf);
     if (rv == APR_SUCCESS) {
         rv = ap_regkey_value_array_set(key, "ConfigArgs", argc, argv, pconf);
         ap_regkey_close(key);
     }
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
-                     "%s: Failed to store the ConfigArgs in the registry.", 
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+                     "%s: Failed to store the ConfigArgs in the registry.",
                      mpm_display_name);
         return (rv);
     }
     fprintf(stderr,"The %s service is successfully installed.\n", mpm_display_name);
     return APR_SUCCESS;
 }
