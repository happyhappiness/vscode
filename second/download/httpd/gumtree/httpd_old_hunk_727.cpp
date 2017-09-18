    {
        SC_HANDLE schService;
        SC_HANDLE schSCManager;

        fprintf(stderr,"Removing the %s service\n", mpm_display_name);

        // TODO: Determine the minimum permissions required for security
        schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                     SC_MANAGER_ALL_ACCESS);
        if (!schSCManager) {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "Failed to open the WinNT service manager.");
            return (rv);
        }
        
        schService = OpenService(schSCManager, mpm_service_name, SERVICE_ALL_ACCESS);

        if (!schService) {
           rv = apr_get_os_error();
           ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
			"%s: OpenService failed", mpm_display_name);
           return (rv);
