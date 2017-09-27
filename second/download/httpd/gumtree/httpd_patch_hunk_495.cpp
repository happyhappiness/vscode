     }
 
     /* Create a pipe to send handles to the child */
     if ((rv = apr_procattr_io_set(attr, APR_FULL_BLOCK, 
                                   APR_NO_PIPE, APR_NO_PIPE)) != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
-                        "Parent: Unable to create child stdin pipe.\n");
+                        "Parent: Unable to create child stdin pipe.");
         apr_pool_destroy(ptemp);
         return -1;
     }
 
     /* Open a null handle to soak info from the child */
     if (((rv = apr_file_open(&child_out, "NUL", APR_READ | APR_WRITE, 
                              APR_OS_DEFAULT, ptemp)) != APR_SUCCESS)
         || ((rv = apr_procattr_child_out_set(attr, child_out, NULL)) 
                 != APR_SUCCESS)) {
         ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
-                        "Parent: Unable to connect child stdout to NUL.\n");
+                        "Parent: Unable to connect child stdout to NUL.");
         apr_pool_destroy(ptemp);
         return -1;
     }
 
     /* Connect the child's initial stderr to our main server error log 
      * or share our own stderr handle.
