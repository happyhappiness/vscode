     schSCManager = OpenSCManager(NULL, NULL, /* default machine & database */
                                  SC_MANAGER_CONNECT);
 
     if (!schSCManager) {
         ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP,
                      apr_get_os_error(), NULL,
-                     APLOGNO(00369)  "Failed to open the Windows service "
+                     APLOGNO(10013)  "Failed to open the Windows service "
                      "manager, perhaps you forgot to log in as Adminstrator?");
         return;
     }
 
 #if APR_HAS_UNICODE_FS
     IF_WIN_OS_IS_UNICODE
