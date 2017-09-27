                        APR_READ | APR_WRITE | APR_CREATE, pconf);
    if (rv == APR_SUCCESS) {
        rv = ap_regkey_value_array_set(key, "ConfigArgs", argc, argv, pconf);
        ap_regkey_close(key);
    }
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, APLOGNO(00371)
                     "%s: Failed to store the ConfigArgs in the registry.",
                     mpm_display_name);
        return (rv);
    }
    fprintf(stderr,"The %s service is successfully installed.\n", mpm_display_name);
    return APR_SUCCESS;
}


apr_status_t mpm_service_uninstall(void)
{
    apr_status_t rv;
    SC_HANDLE schService;
    SC_HANDLE schSCManager;

    fprintf(stderr,"Removing the %s service\n", mpm_display_name);

    schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                 SC_MANAGER_CONNECT);
    if (!schSCManager) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, APLOGNO(00372)
                     "Failed to open the WinNT service manager.");
        return (rv);
    }

    /* ###: utf-ize */
    schService = OpenService(schSCManager, mpm_service_name, DELETE);

    if (!schService) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, APLOGNO(00373)
                        "%s: OpenService failed", mpm_display_name);
        return (rv);
    }

    /* assure the service is stopped before continuing
     *
     * This may be out of order... we might not be able to be
