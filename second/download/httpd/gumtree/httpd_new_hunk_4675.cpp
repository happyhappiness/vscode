
    schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                 SC_MANAGER_CONNECT);
    if (!schSCManager) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     APLOGNO(10011)  "Failed to open the Windows service "
                     "manager, perhaps you forgot to log in as Adminstrator?");
        return (rv);
    }

#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
