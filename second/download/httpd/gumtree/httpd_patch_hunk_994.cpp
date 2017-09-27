 
     if (!strcmp(dash_k_arg, "graceful")) {
         if (!running) {
             printf("httpd not running, trying to start\n");
         }
         else {
-            *exit_status = send_signal(otherpid, SIGUSR1);
+            *exit_status = send_signal(otherpid, AP_SIG_GRACEFUL);
             return 1;
         }
     }
 
+    if (!strcmp(dash_k_arg, "graceful-stop")) {
+#ifdef AP_MPM_WANT_SET_GRACEFUL_SHUTDOWN
+        if (!running) {
+            printf("%s\n", status);
+        }
+        else {
+            *exit_status = send_signal(otherpid, AP_SIG_GRACEFUL_STOP);
+        }
+#else
+        printf("httpd MPM \"" MPM_NAME "\" does not support graceful-stop\n");
+#endif
+        return 1;
+    }
+
     return 0;
 }
 
 void ap_mpm_rewrite_args(process_rec *process)
 {
     apr_array_header_t *mpm_new_argv;
