    }
    else /* osver.dwPlatformId != VER_PLATFORM_WIN32_NT */
    {
        /* Store the launch command in the registry */
        launch_cmd = apr_psprintf(ptemp, "\"%s\" -n %s -k runservice", 
                                 exe_path, mpm_service_name);
        rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, SERVICECONFIG9X, 
                            APR_READ | APR_WRITE | APR_CREATE, pconf);
        if (rv == APR_SUCCESS) {
            rv = ap_regkey_value_set(key, mpm_service_name, 
                                     launch_cmd, 0, pconf);
            ap_regkey_close(key);
        }
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                         "%s: Failed to add the RunServices registry entry.", 
                         mpm_display_name);
            return (rv);
        }

        apr_snprintf(key_name, sizeof(key_name), SERVICECONFIG, mpm_service_name);
        rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, key_name, 
                            APR_READ | APR_WRITE | APR_CREATE, pconf);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                         "%s: Failed to create the registry service key.", 
                         mpm_display_name);
            return (rv);
        }
        rv = ap_regkey_value_set(key, "ImagePath", launch_cmd, 0, pconf);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                         "%s: Failed to store ImagePath in the registry.", 
                         mpm_display_name);
            ap_regkey_close(key);
            return (rv);
        }
        rv = ap_regkey_value_set(key, "DisplayName", 
                                 mpm_display_name, 0, pconf);
        ap_regkey_close(key);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                         "%s: Failed to store DisplayName in the registry.", 
                         mpm_display_name);
            return (rv);
        }
