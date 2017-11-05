apr_status_t mpm_service_uninstall(void)
{
    apr_status_t rv;
    SC_HANDLE schService;
    SC_HANDLE schSCManager;

    fprintf(stderr, "Removing the '%s' service\n", mpm_display_name);

    schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                 SC_MANAGER_CONNECT);
    if (!schSCManager) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     APLOGNO(00369)  "Failed to open the Windows service "
                     "manager, perhaps you forgot to log in as Adminstrator?");
        return (rv);
    }

#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
    {
        schService = OpenServiceW(schSCManager, mpm_service_name_w, DELETE);
    }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
    ELSE_WIN_OS_IS_ANSI
    {
        schService = OpenService(schSCManager, mpm_service_name, DELETE);
    }
#endif
    if (!schService) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     APLOGNO(00373) "Failed to open the '%s' service",
                     mpm_display_name);
        return (rv);
    }

    /* assure the service is stopped before continuing
     *
     * This may be out of order... we might not be able to be
     * granted all access if the service is running anyway.
     *
     * And do we want to make it *this easy* for them
     * to uninstall their service unintentionally?
     */
    /* ap_stop_service(schService);
     */

    if (DeleteService(schService) == 0) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     APLOGNO(00374) "Failed to delete the '%s' service",
                     mpm_display_name);
        return (rv);
    }

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);

    fprintf(stderr, "The '%s' service has been removed successfully.\n",
                    mpm_display_name);
    return APR_SUCCESS;
}