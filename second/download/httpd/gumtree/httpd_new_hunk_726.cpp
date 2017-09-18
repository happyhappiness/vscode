
    set_service_description();

    /* For both WinNT & Win9x store the service ConfigArgs in the registry...
     */
    apr_snprintf(key_name, sizeof(key_name), SERVICEPARAMS, mpm_service_name);
    rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, key_name, 
                        APR_READ | APR_WRITE | APR_CREATE, pconf);
    if (rv == APR_SUCCESS) {
        rv = ap_regkey_value_array_set(key, "ConfigArgs", argc, argv, pconf);
        ap_regkey_close(key);
    }
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                     "%s: Failed to store the ConfigArgs in the registry.", 
                     mpm_display_name);
        return (rv);
    }
