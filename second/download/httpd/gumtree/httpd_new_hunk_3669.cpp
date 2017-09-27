    SC_HANDLE   schSCManager;

    schSCManager = OpenSCManager(NULL, NULL, /* default machine & database */
                                 SC_MANAGER_CONNECT);

    if (!schSCManager) {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP,
                     apr_get_os_error(), NULL,
                     APLOGNO(00369)  "Failed to open the Windows service "
                     "manager, perhaps you forgot to log in as Adminstrator?");
        return;
    }

#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
    {
        schService = OpenServiceW(schSCManager, mpm_service_name_w,
                                  SERVICE_INTERROGATE | SERVICE_QUERY_STATUS |
                                  SERVICE_USER_DEFINED_CONTROL |
                                  SERVICE_START | SERVICE_STOP);
    }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
    ELSE_WIN_OS_IS_ANSI
    {
        schService = OpenService(schSCManager, mpm_service_name,
                                 SERVICE_INTERROGATE | SERVICE_QUERY_STATUS |
                                 SERVICE_USER_DEFINED_CONTROL |
                                 SERVICE_START | SERVICE_STOP);
    }
#endif
    if (schService == NULL) {
        /* Could not open the service */
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP,
                     apr_get_os_error(), NULL,
                     APLOGNO(00373) "Failed to open the '%s' service",
                     mpm_display_name);
        CloseServiceHandle(schSCManager);
        return;
    }

    if (!QueryServiceStatus(schService, &globdat.ssStatus)) {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP,
                     apr_get_os_error(), NULL,
                     APLOGNO(00381) "Query of the '%s' service failed",
                     mpm_display_name);
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return;
    }

    if (!signal && (globdat.ssStatus.dwCurrentState == SERVICE_STOPPED)) {
        fprintf(stderr, "The '%s' service is not started.\n", mpm_display_name);
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return;
    }

    fprintf(stderr, signal ? "The '%s' service is restarting.\n"
                           : "The '%s' service is stopping.\n",
                    mpm_display_name);

    if (!signal)
        success = signal_service_transition(schService,
                                            SERVICE_CONTROL_STOP,
                                            SERVICE_STOP_PENDING,
                                            SERVICE_STOPPED);
