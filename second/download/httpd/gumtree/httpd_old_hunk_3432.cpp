

apr_status_t mpm_service_start(apr_pool_t *ptemp, int argc,
                               const char * const * argv)
{
    apr_status_t rv;
    char **start_argv;
    SC_HANDLE   schService;
    SC_HANDLE   schSCManager;

    fprintf(stderr,"Starting the %s service\n", mpm_display_name);

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
    }

    if (QueryServiceStatus(schService, &globdat.ssStatus)
        && (globdat.ssStatus.dwCurrentState == SERVICE_RUNNING)) {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, 0, NULL,
                     "Service %s is already started!", mpm_display_name);
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return 0;
    }

