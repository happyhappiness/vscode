

apr_status_t mpm_service_install(apr_pool_t *ptemp, int argc,
                                 const char * const * argv, int reconfig)
{
    char key_name[MAX_PATH];
    char *launch_cmd;
    ap_regkey_t *key;
    apr_status_t rv;
    SC_HANDLE   schService;
    SC_HANDLE   schSCManager;
    DWORD       rc;
#if APR_HAS_UNICODE_FS
    apr_wchar_t *display_name_w;
    apr_wchar_t *launch_cmd_w;
#endif

    fprintf(stderr, reconfig ? "Reconfiguring the '%s' service\n"
                             : "Installing the '%s' service\n",
                    mpm_display_name);

#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
    {
        apr_size_t slen = strlen(mpm_display_name) + 1;
        apr_size_t wslen = slen;
        display_name_w = apr_palloc(ptemp, wslen * sizeof(apr_wchar_t));
        rv = apr_conv_utf8_to_ucs2(mpm_display_name, &slen,
                                   display_name_w, &wslen);
        if (rv != APR_SUCCESS)
            return rv;
        else if (slen)
            return APR_ENAMETOOLONG;

        launch_cmd_w = apr_palloc(ptemp, (MAX_PATH + 17) * sizeof(apr_wchar_t));
        launch_cmd_w[0] = L'"';
        rc = GetModuleFileNameW(NULL, launch_cmd_w + 1, MAX_PATH);
        wcscpy(launch_cmd_w + rc + 1, L"\" -k runservice");
    }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
    ELSE_WIN_OS_IS_ANSI
    {
        launch_cmd = apr_palloc(ptemp, MAX_PATH + 17);
        launch_cmd[0] = '"';
        rc = GetModuleFileName(NULL, launch_cmd + 1, MAX_PATH);
        strcpy(launch_cmd + rc + 1, "\" -k runservice");
    }
#endif
    if (rc == 0) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     APLOGNO(00368) "GetModuleFileName failed");
        return rv;
    }

    schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                 SC_MANAGER_CREATE_SERVICE);
    if (!schSCManager) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     APLOGNO(00369)  "Failed to open the Windows service "
                     "manager, perhaps you forgot to log in as Adminstrator?");
        return (rv);
    }

    if (reconfig) {
#if APR_HAS_UNICODE_FS
        IF_WIN_OS_IS_UNICODE
        {
            schService = OpenServiceW(schSCManager, mpm_service_name_w,
                                      SERVICE_CHANGE_CONFIG);
        }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
        ELSE_WIN_OS_IS_ANSI
        {
            schService = OpenService(schSCManager, mpm_service_name,
                                     SERVICE_CHANGE_CONFIG);
        }
#endif
        if (!schService) {
            rv = apr_get_os_error();
            CloseServiceHandle(schSCManager);
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         APLOGNO(00373) "Failed to open the '%s' service",
                         mpm_display_name);
            return (rv);
        }

#if APR_HAS_UNICODE_FS
        IF_WIN_OS_IS_UNICODE
        {
            rc = ChangeServiceConfigW(schService,
                                      SERVICE_WIN32_OWN_PROCESS,
                                      SERVICE_AUTO_START,
                                      SERVICE_ERROR_NORMAL,
                                      launch_cmd_w, NULL, NULL,
                                      L"Tcpip\0Afd\0", NULL, NULL,
                                      display_name_w);
        }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
        ELSE_WIN_OS_IS_ANSI
        {
            rc = ChangeServiceConfig(schService,
                                     SERVICE_WIN32_OWN_PROCESS,
                                     SERVICE_AUTO_START,
                                     SERVICE_ERROR_NORMAL,
                                     launch_cmd, NULL, NULL,
                                     "Tcpip\0Afd\0", NULL, NULL,
                                     mpm_display_name);
        }
#endif
        if (!rc) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP,
                         apr_get_os_error(), NULL,
                         APLOGNO(02652) "ChangeServiceConfig failed");

            /* !schService aborts configuration below */
            CloseServiceHandle(schService);
            schService = NULL;
        }
    }
    else {
        /* RPCSS is the Remote Procedure Call (RPC) Locator required
         * for DCOM communication pipes.  I am far from convinced we
         * should add this to the default service dependencies, but
         * be warned that future apache modules or ISAPI dll's may
         * depend on it.
         */
#if APR_HAS_UNICODE_FS
        IF_WIN_OS_IS_UNICODE
        {
            schService = CreateServiceW(schSCManager,    // SCManager database
                                 mpm_service_name_w,   // name of service
                                 display_name_w,   // name to display
                                 SERVICE_ALL_ACCESS,   // access required
                                 SERVICE_WIN32_OWN_PROCESS,  // service type
                                 SERVICE_AUTO_START,   // start type
                                 SERVICE_ERROR_NORMAL, // error control type
                                 launch_cmd_w,         // service's binary
                                 NULL,                 // no load svc group
                                 NULL,                 // no tag identifier
                                 L"Tcpip\0Afd\0",      // dependencies
                                 NULL,                 // use SYSTEM account
                                 NULL);                // no password
        }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
        ELSE_WIN_OS_IS_ANSI
        {
            schService = CreateService(schSCManager,     // SCManager database
                                 mpm_service_name,     // name of service
                                 mpm_display_name,     // name to display
                                 SERVICE_ALL_ACCESS,   // access required
                                 SERVICE_WIN32_OWN_PROCESS,  // service type
                                 SERVICE_AUTO_START,   // start type
                                 SERVICE_ERROR_NORMAL, // error control type
                                 launch_cmd,           // service's binary
                                 NULL,                 // no load svc group
                                 NULL,                 // no tag identifier
                                 "Tcpip\0Afd\0",       // dependencies
                                 NULL,                 // use SYSTEM account
                                 NULL);                // no password
        }
#endif
        if (!schService)
        {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         APLOGNO(00370) "Failed to create the '%s' service",
                         mpm_display_name);
            CloseServiceHandle(schSCManager);
            return (rv);
        }
    }

    CloseServiceHandle(schService);
