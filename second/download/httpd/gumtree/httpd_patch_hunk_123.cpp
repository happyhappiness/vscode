             return;
         }
 
         /* ###: utf-ize */
         schService = OpenService(schSCManager, mpm_service_name, 
                                  SERVICE_INTERROGATE | SERVICE_QUERY_STATUS | 
+                                 SERVICE_USER_DEFINED_CONTROL |
                                  SERVICE_START | SERVICE_STOP);
 
         if (schService == NULL) {
             /* Could not open the service */
             ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), NULL,
                          "Failed to open the %s Service", mpm_display_name);
