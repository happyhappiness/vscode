        ((status = apr_procattr_error_check_set(procattr, 1)) != APR_SUCCESS)) {
        char buf[120];
        /* Something bad happened, give up and go away. */
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "piped_log_spawn: unable to setup child process '%s': %s",
                     pl->program, apr_strerror(status, buf, sizeof(buf)));
        rc = -1;
    }
    else {
        char **args;
        const char *pname;

        apr_tokenize_to_argv(pl->program, &args, pl->p);
