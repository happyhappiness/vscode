     CloseServiceHandle(schService);
     CloseServiceHandle(schSCManager);
 
     if (rv == APR_SUCCESS)
         fprintf(stderr,"The %s service is running.\n", mpm_display_name);
     else
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL, APLOGNO(00378)
                      "%s: Failed to start the service process.",
                      mpm_display_name);
 
     return rv;
 }
 
