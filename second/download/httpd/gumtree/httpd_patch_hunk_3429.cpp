                         APR_READ | APR_WRITE | APR_CREATE, pconf);
     if (rv == APR_SUCCESS) {
         rv = ap_regkey_value_array_set(key, "ConfigArgs", argc, argv, pconf);
         ap_regkey_close(key);
     }
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, APLOGNO(00371)
                      "%s: Failed to store the ConfigArgs in the registry.",
                      mpm_display_name);
         return (rv);
     }
     fprintf(stderr,"The %s service is successfully installed.\n", mpm_display_name);
     return APR_SUCCESS;
