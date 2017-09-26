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
