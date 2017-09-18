        
        CloseServiceHandle(schService);        
        CloseServiceHandle(schSCManager);
    }
    else /* osver.dwPlatformId != VER_PLATFORM_WIN32_NT */
    {
        fprintf(stderr,"Removing the %s service\n", mpm_display_name);

        /* TODO: assure the service is stopped before continuing */

        if (ap_registry_delete_value(SERVICECONFIG9X, mpm_service_name)) {
            rv = apr_get_os_error();
	    ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "%s: Failed to remove the RunServices registry "
                         "entry.", mpm_display_name);
            return (rv);
        }
        
        /* we blast Services/us, not just the Services/us/Parameters branch */
        apr_snprintf(key_name, sizeof(key_name), SERVICECONFIG, mpm_service_name);
        if (ap_registry_delete_key(key_name)) 
        {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "%s: Failed to remove the service config from the "
                         "registry.", mpm_display_name);
            return (rv);
        }
    }
    fprintf(stderr,"The %s service has been removed successfully.\n", mpm_display_name);
    return APR_SUCCESS;
}


