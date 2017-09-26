                            APR_OS_DEFAULT, p)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                     "%s: could not open error log file %s.",
                     ap_server_argv0, fname);
        return rc;
    }
    if ((rc = apr_file_open_stderr(&stderr_log, p)) == APR_SUCCESS) {
        apr_file_flush(stderr_log);
        if ((rc = apr_file_dup2(stderr_log, stderr_file, p)) == APR_SUCCESS) {
            apr_file_close(stderr_file);
        }
    }
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rc, NULL,
                     "unable to replace stderr with error_log");
    }
    return rc;
}

static void log_child_errfn(apr_pool_t *pool, apr_status_t err,
                            const char *description)
