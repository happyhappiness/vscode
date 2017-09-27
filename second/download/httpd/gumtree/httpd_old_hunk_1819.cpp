                     "piped_log_spawn: unable to setup child process '%s': %s",
                     pl->program, apr_strerror(status, buf, sizeof(buf)));
    }
    else {
        char **args;
        const char *pname;
        apr_file_t *outfile, *errfile;

        if ((status = apr_file_open_stdout(&outfile, pl->p)) == APR_SUCCESS)
            status = apr_procattr_child_out_set(procattr, outfile, NULL);
        if ((status = apr_file_open_stderr(&errfile, pl->p)) == APR_SUCCESS)
            status = apr_procattr_child_err_set(procattr, errfile, NULL);

        apr_tokenize_to_argv(pl->program, &args, pl->p);
        pname = apr_pstrdup(pl->p, args[0]);
        procnew = apr_pcalloc(pl->p, sizeof(apr_proc_t));
        status = apr_proc_create(procnew, pname, (const char * const *) args,
                                 NULL, procattr, pl->p);

        if (status == APR_SUCCESS) {
            pl->pid = procnew;
            /* procnew->in was dup2'd from ap_piped_log_write_fd(pl);
             * since the original fd is still valid, close the copy to
             * avoid a leak. */
            apr_file_close(procnew->in);
            procnew->in = NULL;
            apr_proc_other_child_register(procnew, piped_log_maintenance, pl,
                                          ap_piped_log_write_fd(pl), pl->p);
            close_handle_in_child(pl->p, ap_piped_log_read_fd(pl));
        }
        else {
            char buf[120];
            /* Something bad happened, give up and go away. */
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "unable to start piped log program '%s': %s",
