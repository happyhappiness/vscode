         ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                         "Parent: Unable to create child stdin pipe.");
         apr_pool_destroy(ptemp);
         return -1;
     }
 
+    /* httpd-2.0/2.2 specific to work around apr_proc_create bugs */
+    if (((rv = apr_file_open_stdout(&child_out, p))
+            != APR_SUCCESS) ||
+        ((rv = apr_procattr_child_out_set(attr, child_out, NULL))
+            != APR_SUCCESS)) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
+                     "Parent: Could not set child process stdout");
+    }
+    if (((rv = apr_file_open_stderr(&child_err, p))
+            != APR_SUCCESS) ||
+        ((rv = apr_procattr_child_err_set(attr, child_err, NULL))
+            != APR_SUCCESS)) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
+                     "Parent: Could not set child process stderr");
+    }
+
     /* Create the child_ready_event */
     waitlist[waitlist_ready] = CreateEvent(NULL, TRUE, FALSE, NULL);
     if (!waitlist[waitlist_ready]) {
         ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                      "Parent: Could not create ready event for child process");
         apr_pool_destroy (ptemp);
