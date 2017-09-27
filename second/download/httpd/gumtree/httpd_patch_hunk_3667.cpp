      */
     /* ap_stop_service(schService);
      */
 
     if (DeleteService(schService) == 0) {
         rv = apr_get_os_error();
-        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, APLOGNO(00374)
-                     "%s: Failed to delete the service.", mpm_display_name);
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+                     APLOGNO(00374) "Failed to delete the '%s' service",
+                     mpm_display_name);
         return (rv);
     }
 
     CloseServiceHandle(schService);
     CloseServiceHandle(schSCManager);
 
-    fprintf(stderr,"The %s service has been removed successfully.\n", mpm_display_name);
+    fprintf(stderr, "The '%s' service has been removed successfully.\n",
+                    mpm_display_name);
     return APR_SUCCESS;
 }
 
 
 /* signal_service_transition is a simple thunk to signal the service
  * and monitor its successful transition.  If the signal passed is 0,
  * then the caller is assumed to already have performed some service
  * operation to be monitored (such as StartService), and no actual
  * ControlService signal is sent.
  */
 
-static int signal_service_transition(SC_HANDLE schService, DWORD signal, DWORD pending, DWORD complete)
+static int signal_service_transition(SC_HANDLE schService, DWORD signal,
+                                     DWORD pending, DWORD complete)
 {
     if (signal && !ControlService(schService, signal, &globdat.ssStatus))
         return FALSE;
 
     do {
         Sleep(1000);
