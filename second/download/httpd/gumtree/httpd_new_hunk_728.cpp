        
        CloseServiceHandle(schService);        
        CloseServiceHandle(schSCManager);
    }
    else /* osver.dwPlatformId != VER_PLATFORM_WIN32_NT */
    {
        apr_status_t rv2, rv3;
        ap_regkey_t *key;
        fprintf(stderr,"Removing the %s service\n", mpm_display_name);

        /* TODO: assure the service is stopped before continuing */

        rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, SERVICECONFIG9X, 
                            APR_READ | APR_WRITE | APR_CREATE, pconf);
        if (rv == APR_SUCCESS) {
            rv = ap_regkey_value_remove(key, mpm_service_name, pconf);
            ap_regkey_close(key);
        }
        if (rv != APR_SUCCESS) {
	    ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "%s: Failed to remove the RunServices registry "
                         "entry.", mpm_display_name);
        }
        
        /* we blast Services/us, not just the Services/us/Parameters branch */
        apr_snprintf(key_name, sizeof(key_name), SERVICEPARAMS, mpm_service_name);
        rv2 = ap_regkey_remove(AP_REGKEY_LOCAL_MACHINE, key_name, pconf);
        apr_snprintf(key_name, sizeof(key_name), SERVICECONFIG, mpm_service_name);
        rv3 = ap_regkey_remove(AP_REGKEY_LOCAL_MACHINE, key_name, pconf);
        rv2 = (rv2 != APR_SUCCESS) ? rv2 : rv3;
        if (rv2 != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv2, NULL,
                         "%s: Failed to remove the service config from the "
                         "registry.", mpm_display_name);
        }
        rv = (rv != APR_SUCCESS) ? rv : rv2;
        if (rv != APR_SUCCESS)
            return rv;
    }
    fprintf(stderr,"The %s service has been removed successfully.\n", mpm_display_name);
    return APR_SUCCESS;
}


