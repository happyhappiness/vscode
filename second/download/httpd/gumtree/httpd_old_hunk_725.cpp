    }
    else /* osver.dwPlatformId != VER_PLATFORM_WIN32_NT */
    {
        /* Store the launch command in the registry */
        launch_cmd = apr_psprintf(ptemp, "\"%s\" -n %s -k runservice", 
                                 exe_path, mpm_service_name);
        rv = ap_registry_store_value(SERVICECONFIG9X, mpm_service_name, launch_cmd);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                         "%s: Failed to add the RunServices registry entry.", 
                         mpm_display_name);
            return (rv);
        }

        apr_snprintf(key_name, sizeof(key_name), SERVICECONFIG, mpm_service_name);
        rv = ap_registry_store_value(key_name, "ImagePath", launch_cmd);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                         "%s: Failed to store ImagePath in the registry.", 
                         mpm_display_name);
            return (rv);
        }
        rv = ap_registry_store_value(key_name, "DisplayName", mpm_display_name);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                         "%s: Failed to store DisplayName in the registry.", 
                         mpm_display_name);
            return (rv);
        }
