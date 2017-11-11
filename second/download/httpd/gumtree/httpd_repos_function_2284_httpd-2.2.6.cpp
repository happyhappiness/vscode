apr_status_t mpm_service_install(apr_pool_t *ptemp, int argc,
                                 const char * const * argv, int reconfig)
{
    char key_name[MAX_PATH];
    char exe_path[MAX_PATH];
    char *launch_cmd;
    ap_regkey_t *key;
    apr_status_t rv;

    fprintf(stderr,reconfig ? "Reconfiguring the %s service\n"
                   : "Installing the %s service\n", mpm_display_name);

    /* ###: utf-ize */
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

        schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                     SC_MANAGER_CREATE_SERVICE);
        if (!schSCManager) {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "Failed to open the WinNT service manager");
            return (rv);
        }

        launch_cmd = apr_psprintf(ptemp, "\"%s\" -k runservice", exe_path);

        if (reconfig) {
            /* ###: utf-ize */
            schService = OpenService(schSCManager, mpm_service_name,
                                     SERVICE_CHANGE_CONFIG);
            if (!schService) {
                ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_ERR,
                             apr_get_os_error(), NULL,
                             "OpenService failed");
            }
            /* ###: utf-ize */
            else if (!ChangeServiceConfig(schService,
                                          SERVICE_WIN32_OWN_PROCESS,
                                          SERVICE_AUTO_START,
                                          SERVICE_ERROR_NORMAL,
                                          launch_cmd, NULL, NULL,
                                          "Tcpip\0Afd\0", NULL, NULL,
                                          mpm_display_name)) {
                ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_ERR,
                             apr_get_os_error(), NULL,
                             "ChangeServiceConfig failed");
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
            /* ###: utf-ize */
            schService = CreateService(schSCManager,         // SCManager database
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

            if (!schService)
            {
                rv = apr_get_os_error();
                ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                             "Failed to create WinNT Service Profile");
                CloseServiceHandle(schSCManager);
                return (rv);
            }
        }

        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
    }
    else /* osver.dwPlatformId != VER_PLATFORM_WIN32_NT */
    {
        /* Store the launch command in the registry */
        launch_cmd = apr_psprintf(ptemp, "\"%s\" -n %s -k runservice",
                                 exe_path, mpm_service_name);
        rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, SERVICECONFIG9X,
                            APR_READ | APR_WRITE | APR_CREATE, pconf);
        if (rv == APR_SUCCESS) {
            rv = ap_regkey_value_set(key, mpm_service_name,
                                     launch_cmd, 0, pconf);
            ap_regkey_close(key);
        }
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "%s: Failed to add the RunServices registry entry.",
                         mpm_display_name);
            return (rv);
        }

        apr_snprintf(key_name, sizeof(key_name), SERVICECONFIG, mpm_service_name);
        rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, key_name,
                            APR_READ | APR_WRITE | APR_CREATE, pconf);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "%s: Failed to create the registry service key.",
                         mpm_display_name);
            return (rv);
        }
        rv = ap_regkey_value_set(key, "ImagePath", launch_cmd, 0, pconf);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "%s: Failed to store ImagePath in the registry.",
                         mpm_display_name);
            ap_regkey_close(key);
            return (rv);
        }
        rv = ap_regkey_value_set(key, "DisplayName",
                                 mpm_display_name, 0, pconf);
        ap_regkey_close(key);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "%s: Failed to store DisplayName in the registry.",
                         mpm_display_name);
            return (rv);
        }
    }

    set_service_description();

    /* For both WinNT & Win9x store the service ConfigArgs in the registry...
     */
    apr_snprintf(key_name, sizeof(key_name), SERVICEPARAMS, mpm_service_name);
    rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, key_name,
                        APR_READ | APR_WRITE | APR_CREATE, pconf);
    if (rv == APR_SUCCESS) {
        rv = ap_regkey_value_array_set(key, "ConfigArgs", argc, argv, pconf);
        ap_regkey_close(key);
    }
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     "%s: Failed to store the ConfigArgs in the registry.",
                     mpm_display_name);
        return (rv);
    }
    fprintf(stderr,"The %s service is successfully installed.\n", mpm_display_name);
    return APR_SUCCESS;
}