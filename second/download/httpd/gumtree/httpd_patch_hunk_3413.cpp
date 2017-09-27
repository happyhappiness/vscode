     }
 
     if (!strcasecmp(signal_arg, "install")) /* -k install */
     {
         if (service_set == APR_SUCCESS)
         {
-            ap_log_error(APLOG_MARK,APLOG_ERR, 0, NULL,
+            ap_log_error(APLOG_MARK,APLOG_ERR, 0, NULL, APLOGNO(00433)
                  "%s: Service is already installed.", service_name);
             exit(APEXIT_INIT);
         }
     }
     else if (running_as_service)
     {
