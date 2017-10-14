void mpm_signal_service(apr_pool_t *ptemp, int signal)
{
    int success = FALSE;

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
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), NULL,
                         "Failed to open the %s Service", mpm_display_name);
            CloseServiceHandle(schSCManager);
            return;
        }

        if (!QueryServiceStatus(schService, &globdat.ssStatus)) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), NULL,
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
        else if (globdat.ssStatus.dwCurrentState == SERVICE_STOPPED) {
            mpm_service_start(ptemp, 0, NULL);
            CloseServiceHandle(schService);
            CloseServiceHandle(schSCManager);
            return;
        }
        else
            success = signal_service_transition(schService,
                                                SERVICE_APACHE_RESTART,
                                                SERVICE_START_PENDING,
                                                SERVICE_RUNNING);

        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
    }
    else /* !isWindowsNT() */
    {
        DWORD       service_pid;
        HANDLE      hwnd;
        char prefix[20];
        /* Locate the active top level window named service_name
         * provided the class is ApacheWin95ServiceMonitor
         */
        hwnd = FindWindow("ApacheWin95ServiceMonitor", mpm_service_name);
        if (hwnd && GetWindowThreadProcessId(hwnd, &service_pid))
            globdat.ssStatus.dwCurrentState = SERVICE_RUNNING;
        else
        {
            globdat.ssStatus.dwCurrentState = SERVICE_STOPPED;
            if (!signal) {
                fprintf(stderr,"The %s service is not started.\n", mpm_display_name);
                return;
            }
        }

        fprintf(stderr,"The %s service is %s.\n", mpm_display_name,
               signal ? "restarting" : "stopping");

        apr_snprintf(prefix, sizeof(prefix), "ap%ld", (long)service_pid);
        setup_signal_names(prefix);

        if (!signal)
        {
            int ticks = 60;
            ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
            while (--ticks)
            {
                if (!IsWindow(hwnd)) {
                    success = TRUE;
                    break;
                }
                Sleep(1000);
            }
        }
        else /* !stop */
        {
            /* TODO: Aught to add a little test to the restart logic, and
             * store the restart counter in the window's user dword.
             * Then we can hang on and report a successful restart.  But
             * that's a project for another day.
             */
            if (globdat.ssStatus.dwCurrentState == SERVICE_STOPPED) {
                mpm_service_start(ptemp, 0, NULL);
                return;
            }
            else {
                success = TRUE;
                ap_signal_parent(SIGNAL_PARENT_RESTART);
            }
        }
    }

    if (success)
        fprintf(stderr,"The %s service has %s.\n", mpm_display_name,
               signal ? "restarted" : "stopped");
    else
        fprintf(stderr,"Failed to %s the %s service.\n",
               signal ? "restart" : "stop", mpm_display_name);
}