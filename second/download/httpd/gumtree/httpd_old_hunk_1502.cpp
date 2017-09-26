
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
