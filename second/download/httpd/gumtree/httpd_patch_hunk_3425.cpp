 
     /* ###: utf-ize */
     if (!StartServiceCtrlDispatcher(dispatchTable))
     {
         /* This is a genuine failure of the SCM. */
         rv = apr_get_os_error();
-        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, APLOGNO(00366)
                      "Error starting service control dispatcher");
     }
 
     return (rv);
 }
 
