
    set_service_description();

    /* For both WinNT & Win9x store the service ConfigArgs in the registry...
     */
    apr_snprintf(key_name, sizeof(key_name), SERVICEPARAMS, mpm_service_name);
    rv = ap_registry_store_array(ptemp, key_name, "ConfigArgs", argc, argv);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                     "%s: Failed to store the ConfigArgs in the registry.", 
                     mpm_display_name);
        return (rv);
    }
