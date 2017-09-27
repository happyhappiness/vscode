                 exit(0);
             }
 
             rv = mpm_merge_service_args(process->pool, mpm_new_argv,
                                         fixed_args);
             if (rv == APR_SUCCESS) {
-                ap_log_error(APLOG_MARK,APLOG_INFO, 0, NULL,
+                ap_log_error(APLOG_MARK,APLOG_INFO, 0, NULL, APLOGNO(00434)
                              "Using ConfigArgs of the installed service "
                              "\"%s\".", service_name);
             }
             else  {
-                ap_log_error(APLOG_MARK,APLOG_WARNING, rv, NULL,
+                ap_log_error(APLOG_MARK,APLOG_WARNING, rv, NULL, APLOGNO(00435)
                              "No installed ConfigArgs for the service "
                              "\"%s\", using Apache defaults.", service_name);
             }
         }
         else
         {
-            ap_log_error(APLOG_MARK,APLOG_ERR, service_set, NULL,
+            ap_log_error(APLOG_MARK,APLOG_ERR, service_set, NULL, APLOGNO(00436)
                  "No installed service named \"%s\".", service_name);
             exit(APEXIT_INIT);
         }
     }
     if (strcasecmp(signal_arg, "install") && service_set && service_set != SERVICE_UNSET)
     {
-        ap_log_error(APLOG_MARK,APLOG_ERR, service_set, NULL,
+        ap_log_error(APLOG_MARK,APLOG_ERR, service_set, NULL, APLOGNO(00437)
              "No installed service named \"%s\".", service_name);
         exit(APEXIT_INIT);
     }
 
     /* Track the args actually entered by the user.
      * These will be used for the -k install parameters, as well as
