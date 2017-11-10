apr_status_t mpm_service_start(apr_pool_t *ptemp, int argc,
                               const char * const * argv)
{
    apr_status_t rv;

    fprintf(stderr,"Starting the %s service\n", mpm_display_name);

    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        char **start_argv;
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
        }

        if (QueryServiceStatus(schService, &globdat.ssStatus)
            && (globdat.ssStatus.dwCurrentState == SERVICE_RUNNING)) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, 0, NULL,
                         "Service %s is already started!", mpm_display_name);
            CloseServiceHandle(schService);
            CloseServiceHandle(schSCManager);
            return 0;
        }

        start_argv = malloc((argc + 1) * sizeof(const char **));
        memcpy(start_argv, argv, argc * sizeof(const char **));
        start_argv[argc] = NULL;

        rv = APR_EINIT;
        /* ###: utf-ize */
        if (StartService(schService, argc, start_argv)
            && signal_service_transition(schService, 0, /* test only */
                                         SERVICE_START_PENDING,
                                         SERVICE_RUNNING))
                rv = APR_SUCCESS;

        if (rv != APR_SUCCESS)
            rv = apr_get_os_error();

        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
    }
    else /* osver.dwPlatformId != VER_PLATFORM_WIN32_NT */
    {
        STARTUPINFO si;           /* Filled in prior to call to CreateProcess */
        PROCESS_INFORMATION pi;   /* filled in on call to CreateProcess */
        char exe_path[MAX_PATH];
        char exe_cmd[MAX_PATH * 4];
        char *next_arg;
        int i;

        /* Locate the active top level window named service_name
         * provided the class is ApacheWin95ServiceMonitor
         */
        if (FindWindow("ApacheWin95ServiceMonitor", mpm_service_name)) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, 0, NULL,
                         "Service %s is already started!", mpm_display_name);
            return 0;
        }

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