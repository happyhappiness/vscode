     */
    /* ap_stop_service(schService);
     */

    if (DeleteService(schService) == 0) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, APLOGNO(00374)
                     "%s: Failed to delete the service.", mpm_display_name);
        return (rv);
    }

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
