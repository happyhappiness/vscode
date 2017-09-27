                                 SERVICE_START | SERVICE_QUERY_STATUS);
    }
#endif
    if (!schService) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                     APLOGNO(10012) "Failed to open the '%s' service",
                     mpm_display_name);
        CloseServiceHandle(schSCManager);
        return (rv);
    }

    if (QueryServiceStatus(schService, &globdat.ssStatus)
