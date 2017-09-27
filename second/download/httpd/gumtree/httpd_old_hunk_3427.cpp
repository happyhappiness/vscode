                   : "Installing the %s service\n", mpm_display_name);

    /* ###: utf-ize */
    if (GetModuleFileName(NULL, exe_path, sizeof(exe_path)) == 0)
    {
        apr_status_t rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     "GetModuleFileName failed");
        return rv;
    }

    schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                 SC_MANAGER_CREATE_SERVICE);
    if (!schSCManager) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     "Failed to open the WinNT service manager, perhaps "
                     "you forgot to log in as Adminstrator?");
        return (rv);
    }

    launch_cmd = apr_psprintf(ptemp, "\"%s\" -k runservice", exe_path);
