                                             pl->read_fd,
                                             pl->write_fd))
         != APR_SUCCESS) ||
        ((status = apr_procattr_child_errfn_set(procattr, log_child_errfn))
         != APR_SUCCESS) ||
        ((status = apr_procattr_error_check_set(procattr, 1)) != APR_SUCCESS)) {
        /* Something bad happened, give up and go away. */
        ap_log_error(APLOG_MARK, APLOG_STARTUP, status, NULL, APLOGNO(00103)
                     "piped_log_spawn: unable to setup child process '%s'",
                     pl->program);
    }
    else {
        char **args;
        const char *pname;

        apr_tokenize_to_argv(pl->program, &args, pl->p);
