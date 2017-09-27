         ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                         "Parent: Unable to create child stdin pipe.");
         apr_pool_destroy(ptemp);
         return -1;
     }
 
-    /* Open a null handle to soak info from the child */
-    if (((rv = apr_file_open(&child_out, "NUL", APR_READ | APR_WRITE, 
-                             APR_OS_DEFAULT, ptemp)) != APR_SUCCESS)
-        || ((rv = apr_procattr_child_out_set(attr, child_out, NULL)) 
-                != APR_SUCCESS)) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
-                        "Parent: Unable to connect child stdout to NUL.");
-        apr_pool_destroy(ptemp);
-        return -1;
-    }
-
-    /* Connect the child's initial stderr to our main server error log 
-     * or share our own stderr handle.
-     */
-    if (ap_server_conf->error_log) {
-        child_err = ap_server_conf->error_log;
-    }
-    else {
-        rv = apr_file_open_stderr(&child_err, ptemp);
-    }
-    if (rv == APR_SUCCESS) {
-        if ((rv = apr_procattr_child_err_set(attr, child_err, NULL))
-                != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
-                            "Parent: Unable to connect child stderr.");
-            apr_pool_destroy(ptemp);
-            return -1;
-        }
-    }
-
     /* Create the child_ready_event */
     waitlist[waitlist_ready] = CreateEvent(NULL, TRUE, FALSE, NULL);
     if (!waitlist[waitlist_ready]) {
         ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                      "Parent: Could not create ready event for child process");
         apr_pool_destroy (ptemp);
