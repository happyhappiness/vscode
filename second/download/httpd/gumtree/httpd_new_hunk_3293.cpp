        return;
    }

    fname = ap_server_root_relative(p, filename);
    if (!fname) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, APR_EBADPATH,
                     NULL, APLOGNO(00097) "Invalid PID file path %s, ignoring.", filename);
        return;
    }

    mypid = getpid();
    if (mypid != saved_pid
        && apr_stat(&finfo, fname, APR_FINFO_MTIME, p) == APR_SUCCESS) {
