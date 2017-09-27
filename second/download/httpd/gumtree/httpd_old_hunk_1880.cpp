    return APR_SUCCESS;
}


apr_status_t mpm_service_uninstall(void)
{
    char key_name[MAX_PATH];
    apr_status_t rv;

    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        SC_HANDLE schService;
        SC_HANDLE schSCManager;

        fprintf(stderr,"Removing the %s service\n", mpm_display_name);

        schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                     SC_MANAGER_CONNECT);
        if (!schSCManager) {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "Failed to open the WinNT service manager.");
            return (rv);
        }

#if APR_HAS_UNICODE_FS
        IF_WIN_OS_IS_UNICODE
        {
            schService = OpenServiceW(schSCManager, mpm_service_name_w, DELETE);
        }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
        ELSE_WIN_OS_IS_ANSI
        {
            schService = OpenService(schSCManager, mpm_service_name, DELETE);
        }
#endif
        if (!schService) {
           rv = apr_get_os_error();
           ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                        "%s: OpenService failed", mpm_display_name);
           return (rv);
        }

        /* assure the service is stopped before continuing
         *
         * This may be out of order... we might not be able to be
         * granted all access if the service is running anyway.
         *
         * And do we want to make it *this easy* for them
         * to uninstall their service unintentionally?
         */
        // ap_stop_service(schService);

        if (DeleteService(schService) == 0) {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "%s: Failed to delete the service.", mpm_display_name);
            return (rv);
        }

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


/* signal_service_transition is a simple thunk to signal the service
