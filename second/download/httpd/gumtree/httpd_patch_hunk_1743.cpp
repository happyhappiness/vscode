             && (service_to_start_success != APR_SUCCESS)) {
         ap_log_error(APLOG_MARK,APLOG_CRIT, service_to_start_success, NULL,
                      "%s: Unable to start the service manager.",
                      service_name);
         exit(APEXIT_INIT);
     }
+    else if (!one_process && !ap_my_generation) {
+        /* Open a null handle to soak stdout in this process.
+         * We need to emulate apr_proc_detach, unix performs this
+         * same check in the pre_config hook (although it is
+         * arguably premature).  Services already fixed this.
+         */
+        apr_file_t *nullfile;
+        apr_status_t rv;
+        apr_pool_t *pproc = apr_pool_parent_get(pconf);
+
+        if ((rv = apr_file_open(&nullfile, "NUL",
+                                APR_READ | APR_WRITE, APR_OS_DEFAULT,
+                                pproc)) == APR_SUCCESS) {
+            apr_file_t *nullstdout;
+            if (apr_file_open_stdout(&nullstdout, pproc)
+                    == APR_SUCCESS)
+                apr_file_dup2(nullstdout, nullfile, pproc);
+            apr_file_close(nullfile);
+        }
+    }
 
     /* Win9x: disable AcceptEx */
     if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
         use_acceptex = 0;
     }
 
