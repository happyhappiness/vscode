apr_status_t mpm_service_install(apr_pool_t *ptemp, int argc, 
                                 const char * const * argv, int reconfig)
{
    char key_name[MAX_PATH];
    char exe_path[MAX_PATH];
    char *launch_cmd;
    apr_status_t(rv);
    
    fprintf(stderr,reconfig ? "Reconfiguring the %s service\n"
		   : "Installing the %s service\n", mpm_display_name);

    if (GetModuleFileName(NULL, exe_path, sizeof(exe_path)) == 0)
    {
        apr_status_t rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     "GetModuleFileName failed");
        return rv;
    }

    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        SC_HANDLE   schService;
        SC_HANDLE   schSCManager;
    
        // TODO: Determine the minimum permissions required for security
        schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                     SC_MANAGER_ALL_ACCESS);
        if (!schSCManager) {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "Failed to open the WinNT service manager");
            return (rv);
        }

        launch_cmd = apr_psprintf(ptemp, "\"%s\" -k runservice", exe_path);

        if (reconfig) {
            schService = OpenService(schSCManager, mpm_service_name, 
                                     SERVICE_ALL_ACCESS);
            if (!schService) {
                ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_ERR, 
                             apr_get_os_error(), NULL,
                             "OpenService failed");
            }
            else if (!ChangeServiceConfig(schService, 
                                          SERVICE_WIN32_OWN_PROCESS,
                                          SERVICE_AUTO_START,
                                          SERVICE_ERROR_NORMAL,
                                          launch_cmd, NULL, NULL, 
                                          "Tcpip\0Afd\0", NULL, NULL,
