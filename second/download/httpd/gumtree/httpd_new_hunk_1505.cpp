        if (!schSCManager) {
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), NULL,
                         "Failed to open the NT Service Manager");
            return;
        }

#if APR_HAS_UNICODE_FS
        IF_WIN_OS_IS_UNICODE
        {
            schService = OpenServiceW(schSCManager, mpm_service_name_w,
                                      SERVICE_INTERROGATE | SERVICE_QUERY_STATUS |
                                      SERVICE_USER_DEFINED_CONTROL |
                                      SERVICE_START | SERVICE_STOP);
        }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
        ELSE_WIN_OS_IS_ANSI
        {
            schService = OpenService(schSCManager, mpm_service_name,
                                     SERVICE_INTERROGATE | SERVICE_QUERY_STATUS |
                                     SERVICE_USER_DEFINED_CONTROL |
                                     SERVICE_START | SERVICE_STOP);
        }
#endif
        if (schService == NULL) {
            /* Could not open the service */
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), NULL,
                         "Failed to open the %s Service", mpm_display_name);
            CloseServiceHandle(schSCManager);
            return;
