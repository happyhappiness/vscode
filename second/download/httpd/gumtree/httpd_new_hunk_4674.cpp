        schService = OpenService(schSCManager, mpm_service_name, DELETE);
    }
#endif
    if (!schService) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     APLOGNO(10010) "Failed to open the '%s' service",
                     mpm_display_name);
        return (rv);
    }

    /* assure the service is stopped before continuing
     *
