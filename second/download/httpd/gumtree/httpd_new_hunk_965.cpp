        /* This may not appear intuitive, but Win9x will not allow a process
         * to detach from the console without releasing the entire console.
         * Ergo, we must spawn a new process for the service to get back our
         * console window.
         * The config is pre-flighted, so there should be no danger of failure.
         */

        if (GetModuleFileName(NULL, exe_path, sizeof(exe_path)) == 0)
        {
            apr_status_t rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "GetModuleFileName failed");
            return rv;
        }

        apr_snprintf(exe_cmd, sizeof(exe_cmd),
                     "\"%s\" -n %s -k runservice",
                     exe_path, mpm_service_name);
        next_arg = strchr(exe_cmd, '\0');
        for (i = 0; i < argc; ++i) {
            apr_snprintf(next_arg, sizeof(exe_cmd) - (next_arg - exe_cmd),
                         " \"%s\"", argv[i]);
            next_arg = strchr(exe_cmd, '\0');
        }

        memset(&si, 0, sizeof(si));
        memset(&pi, 0, sizeof(pi));
        si.cb = sizeof(si);
        si.dwFlags     = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE;   /* This might be redundant */

        rv = APR_EINIT;
        if (CreateProcess(NULL, exe_cmd, NULL, NULL, FALSE,
                           DETACHED_PROCESS, /* Creation flags */
                           NULL, NULL, &si, &pi))
        {
            DWORD code;
            while (GetExitCodeProcess(pi.hProcess, &code) == STILL_ACTIVE) {
                if (FindWindow("ApacheWin95ServiceMonitor", mpm_service_name)) {
                    rv = APR_SUCCESS;
                    break;
                }
                Sleep (1000);
            }
        }

        if (rv != APR_SUCCESS)
            rv = apr_get_os_error();

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    if (rv == APR_SUCCESS)
        fprintf(stderr,"The %s service is running.\n", mpm_display_name);
    else
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "%s: Failed to start the service process.",
                     mpm_display_name);

    return rv;
}


/* signal is zero to stop, non-zero for restart */

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

        /* ###: utf-ize */
        schService = OpenService(schSCManager, mpm_service_name,
                                 SERVICE_INTERROGATE | SERVICE_QUERY_STATUS |
                                 SERVICE_USER_DEFINED_CONTROL |
                                 SERVICE_START | SERVICE_STOP);

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
