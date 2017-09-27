         ap_process_child_status(&proc, why, status);
         return APR_EINVAL;
     }
     else if (rv != APR_CHILD_NOTDONE) {
         /* The child is already dead and reaped, or was a bogus pid -
          * log this either way. */
-        ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf, APLOGNO(00048)
                      "cannot send signal %d to pid %ld (non-child or "
                      "already dead)", sig, (long)pid);
         return APR_EINVAL;
     }
 #else
     pid_t pg;
 
     /* Ensure pid sanity. */
     if (pid < 1) {
         return APR_EINVAL;
     }
 
-    pg = getpgid(pid);    
+    pg = getpgid(pid);
     if (pg == -1) {
         /* Process already dead... */
         return errno;
     }
 
     if (pg != getpgrp()) {
-        ap_log_error(APLOG_MARK, APLOG_ALERT, 0, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_ALERT, 0, ap_server_conf, APLOGNO(00049)
                      "refusing to send signal %d to pid %ld outside "
                      "process group", sig, (long)pid);
         return APR_EINVAL;
     }
-#endif        
+#endif
 
     return kill(pid, sig) ? errno : APR_SUCCESS;
 }
 
 
 int ap_process_child_status(apr_proc_t *pid, apr_exit_why_e why, int status)
