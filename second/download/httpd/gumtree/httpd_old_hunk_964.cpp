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
