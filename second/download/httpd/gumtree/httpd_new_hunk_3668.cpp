

apr_status_t mpm_service_start(apr_pool_t *ptemp, int argc,
                               const char * const * argv)
{
    apr_status_t rv;
    SC_HANDLE   schService;
    SC_HANDLE   schSCManager;

    fprintf(stderr, "Starting the '%s' service\n", mpm_display_name);

    schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                 SC_MANAGER_CONNECT);
    if (!schSCManager) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     APLOGNO(00369)  "Failed to open the Windows service "
                     "manager, perhaps you forgot to log in as Adminstrator?");
        return (rv);
    }

#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
    {
        schService = OpenServiceW(schSCManager, mpm_service_name_w,
                                  SERVICE_START | SERVICE_QUERY_STATUS);
    }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
    ELSE_WIN_OS_IS_ANSI
    {
        schService = OpenService(schSCManager, mpm_service_name,
                                 SERVICE_START | SERVICE_QUERY_STATUS);
    }
#endif
    if (!schService) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                     APLOGNO(00373) "Failed to open the '%s' service",
                     mpm_display_name);
        CloseServiceHandle(schSCManager);
        return (rv);
    }

    if (QueryServiceStatus(schService, &globdat.ssStatus)
        && (globdat.ssStatus.dwCurrentState == SERVICE_RUNNING)) {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, 0, NULL,
                     APLOGNO(00377) "The '%s' service is already started!",
                     mpm_display_name);
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return 0;
    }

    rv = APR_EINIT;
#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
    {
        LPWSTR *start_argv_w = malloc((argc + 1) * sizeof(LPCWSTR));
        int i;

        for (i = 0; i < argc; ++i)
        {
            apr_size_t slen = strlen(argv[i]) + 1;
            apr_size_t wslen = slen;
            start_argv_w[i] = malloc(wslen * sizeof(WCHAR));
            rv = apr_conv_utf8_to_ucs2(argv[i], &slen, start_argv_w[i], &wslen);
            if (rv != APR_SUCCESS)
                return rv;
            else if (slen)
                return APR_ENAMETOOLONG;
        }
        start_argv_w[argc] = NULL;

        if (StartServiceW(schService, argc, start_argv_w)
            && signal_service_transition(schService, 0, /* test only */
                                         SERVICE_START_PENDING,
                                         SERVICE_RUNNING))
                rv = APR_SUCCESS;
    }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
    ELSE_WIN_OS_IS_ANSI
    {
        char **start_argv = malloc((argc + 1) * sizeof(const char *));
        memcpy(start_argv, argv, argc * sizeof(const char *));
        start_argv[argc] = NULL;

        if (StartService(schService, argc, start_argv)
            && signal_service_transition(schService, 0, /* test only */
                                         SERVICE_START_PENDING,
                                         SERVICE_RUNNING))
                rv = APR_SUCCESS;
    }
#endif
    if (rv != APR_SUCCESS)
        rv = apr_get_os_error();

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);

    if (rv == APR_SUCCESS)
        fprintf(stderr, "The '%s' service is running.\n", mpm_display_name);
    else
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL, APLOGNO(00378)
                     "Failed to start the '%s' service",
                     mpm_display_name);

    return rv;
}


