    fprintf(stderr,"Removing the %s service\n", mpm_display_name);

    schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                 SC_MANAGER_CONNECT);
    if (!schSCManager) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     "Failed to open the WinNT service manager.");
        return (rv);
    }

    /* ###: utf-ize */
    schService = OpenService(schSCManager, mpm_service_name, DELETE);

    if (!schService) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                        "%s: OpenService failed", mpm_display_name);
        return (rv);
    }

    /* assure the service is stopped before continuing
     *
