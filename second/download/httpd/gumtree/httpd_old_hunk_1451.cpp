    apr_status_t rv;

    fprintf(stderr,"Starting the %s service\n", mpm_display_name);

    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        CHAR **start_argv;
        SC_HANDLE   schService;
        SC_HANDLE   schSCManager;

        schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                     SC_MANAGER_CONNECT);
        if (!schSCManager) {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "Failed to open the WinNT service manager");
            return (rv);
        }

        /* ###: utf-ize */
        schService = OpenService(schSCManager, mpm_service_name,
                                 SERVICE_START | SERVICE_QUERY_STATUS);
        if (!schService) {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "%s: Failed to open the service.", mpm_display_name);
            CloseServiceHandle(schSCManager);
            return (rv);
