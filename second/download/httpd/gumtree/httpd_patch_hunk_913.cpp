         if (!signal && (globdat.ssStatus.dwCurrentState == SERVICE_STOPPED)) {
             fprintf(stderr,"The %s service is not started.\n", mpm_display_name);
             CloseServiceHandle(schService);
             CloseServiceHandle(schSCManager);
             return;
         }
-        
-        fprintf(stderr,"The %s service is %s.\n", mpm_display_name, 
+
+        fprintf(stderr,"The %s service is %s.\n", mpm_display_name,
                signal ? "restarting" : "stopping");
 
         if (!signal)
-            success = signal_service_transition(schService, 
-                                                SERVICE_CONTROL_STOP, 
-                                                SERVICE_STOP_PENDING, 
+            success = signal_service_transition(schService,
+                                                SERVICE_CONTROL_STOP,
+                                                SERVICE_STOP_PENDING,
                                                 SERVICE_STOPPED);
         else if (globdat.ssStatus.dwCurrentState == SERVICE_STOPPED) {
             mpm_service_start(ptemp, 0, NULL);
             CloseServiceHandle(schService);
             CloseServiceHandle(schSCManager);
             return;
         }
         else
-            success = signal_service_transition(schService, 
-                                                SERVICE_APACHE_RESTART, 
-                                                SERVICE_START_PENDING, 
+            success = signal_service_transition(schService,
+                                                SERVICE_APACHE_RESTART,
+                                                SERVICE_START_PENDING,
                                                 SERVICE_RUNNING);
 
         CloseServiceHandle(schService);
         CloseServiceHandle(schSCManager);
     }
     else /* !isWindowsNT() */
