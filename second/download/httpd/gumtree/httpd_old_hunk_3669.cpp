    SC_HANDLE   schSCManager;

    schSCManager = OpenSCManager(NULL, NULL, /* default machine & database */
                                 SC_MANAGER_CONNECT);

    if (!schSCManager) {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), NULL, APLOGNO(00379)
                     "Failed to open the NT Service Manager");
        return;
    }

    /* ###: utf-ize */
    schService = OpenService(schSCManager, mpm_service_name,
                             SERVICE_INTERROGATE | SERVICE_QUERY_STATUS |
                             SERVICE_USER_DEFINED_CONTROL |
                             SERVICE_START | SERVICE_STOP);

    if (schService == NULL) {
        /* Could not open the service */
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), NULL, APLOGNO(00380)
                     "Failed to open the %s Service", mpm_display_name);
        CloseServiceHandle(schSCManager);
        return;
    }

    if (!QueryServiceStatus(schService, &globdat.ssStatus)) {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), NULL, APLOGNO(00381)
                     "Query of Service %s failed", mpm_display_name);
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return;
    }

    if (!signal && (globdat.ssStatus.dwCurrentState == SERVICE_STOPPED)) {
        fprintf(stderr,"The %s service is not started.\n", mpm_display_name);
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return;
    }

    fprintf(stderr,"The %s service is %s.\n", mpm_display_name,
            signal ? "restarting" : "stopping");

    if (!signal)
        success = signal_service_transition(schService,
                                            SERVICE_CONTROL_STOP,
                                            SERVICE_STOP_PENDING,
                                            SERVICE_STOPPED);
