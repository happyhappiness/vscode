                                             SERVICE_RUNNING);
 
     CloseServiceHandle(schService);
     CloseServiceHandle(schSCManager);
 
     if (success)
-        fprintf(stderr,"The %s service has %s.\n", mpm_display_name,
-               signal ? "restarted" : "stopped");
+        fprintf(stderr, signal ? "The '%s' service has restarted.\n"
+                               : "The '%s' service has stopped.\n",
+                        mpm_display_name);
     else
-        fprintf(stderr,"Failed to %s the %s service.\n",
-               signal ? "restart" : "stop", mpm_display_name);
+        fprintf(stderr, signal ? "Failed to restart the '%s' service.\n"
+                               : "Failed to stop the '%s' service.\n",
+                        mpm_display_name);
 }
