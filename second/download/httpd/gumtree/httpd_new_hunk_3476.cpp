    const char *status;

    *exit_status = 0;

    rv = ap_read_pid(pconf, ap_pid_fname, &otherpid);
    if (rv != APR_SUCCESS) {
        if (!APR_STATUS_IS_ENOENT(rv)) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, rv, NULL, APLOGNO(00058)
                         "Error retrieving pid file %s", ap_pid_fname);
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00059)
                         "Remove it before continuing if it is corrupted.");
            *exit_status = 1;
            return 1;
        }
        status = "httpd (no pid file) not running";
    }
