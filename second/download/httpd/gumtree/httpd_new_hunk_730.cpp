    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT) 
    {
        SC_HANDLE   schService;
        SC_HANDLE   schSCManager;

        schSCManager = OpenSCManager(NULL, NULL, // default machine & database
                                     SC_MANAGER_CONNECT);
        
        if (!schSCManager) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), NULL,
                         "Failed to open the NT Service Manager");
            return;
        }

        /* ###: utf-ize */
        schService = OpenService(schSCManager, mpm_service_name, 
                                 SERVICE_INTERROGATE | SERVICE_QUERY_STATUS | 
                                 SERVICE_START | SERVICE_STOP);

        if (schService == NULL) {
            /* Could not open the service */
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), NULL,
                         "Failed to open the %s Service", mpm_display_name);
            CloseServiceHandle(schSCManager);
