         != APR_SUCCESS) ||
        ((status = apr_procattr_child_errfn_set(procattr, log_child_errfn))
         != APR_SUCCESS) ||
        ((status = apr_procattr_error_check_set(procattr, 1)) != APR_SUCCESS)) {
        char buf[120];
        /* Something bad happened, give up and go away. */
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00103)
                     "piped_log_spawn: unable to setup child process '%s': %s",
                     pl->program, apr_strerror(status, buf, sizeof(buf)));
    }
    else {
        char **args;
        const char *pname;
