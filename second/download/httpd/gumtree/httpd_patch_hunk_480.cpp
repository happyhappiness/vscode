         procnew = apr_pcalloc(pl->p, sizeof(apr_proc_t));
         status = apr_proc_create(procnew, pname, (const char * const *) args,
                                  NULL, procattr, pl->p);
 
         if (status == APR_SUCCESS) {
             pl->pid = procnew;
-            ap_piped_log_write_fd(pl) = procnew->in;
+            /* procnew->in was dup2'd from ap_piped_log_write_fd(pl);
+             * since the original fd is still valid, close the copy to
+             * avoid a leak. */
+            apr_file_close(procnew->in);
+            procnew->in = NULL;
             apr_proc_other_child_register(procnew, piped_log_maintenance, pl,
                                           ap_piped_log_write_fd(pl), pl->p);
+            close_handle_in_child(pl->p, ap_piped_log_read_fd(pl));
         }
         else {
             char buf[120];
             /* Something bad happened, give up and go away. */
             ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                          "unable to start piped log program '%s': %s",
                          pl->program, apr_strerror(status, buf, sizeof(buf)));
-            rc = -1;
         }
     }
 
-    return rc;
+    return status;
 }
 
 
 static void piped_log_maintenance(int reason, void *data, apr_wait_t status)
 {
     piped_log *pl = data;
