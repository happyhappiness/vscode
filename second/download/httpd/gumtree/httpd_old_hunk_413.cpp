        ((status = apr_procattr_child_in_set(procattr,
                                             ap_piped_log_read_fd(pl),
                                             ap_piped_log_write_fd(pl)))
        != APR_SUCCESS)) {
        char buf[120];
        /* Something bad happened, give up and go away. */
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                     "piped_log_spawn: unable to setup child process '%s': %s",
                     pl->program, apr_strerror(status, buf, sizeof(buf)));
        rc = -1;
    }
    else {
        char **args;
