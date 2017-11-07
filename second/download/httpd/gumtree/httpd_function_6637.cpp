static apr_status_t piped_log_spawn(piped_log *pl)
{
    apr_procattr_t *procattr;
    apr_proc_t *procnew = NULL;
    apr_status_t status;

    if (((status = apr_procattr_create(&procattr, pl->p)) != APR_SUCCESS) ||
        ((status = apr_procattr_dir_set(procattr, ap_server_root))
         != APR_SUCCESS) ||
        ((status = apr_procattr_cmdtype_set(procattr, pl->cmdtype))
         != APR_SUCCESS) ||
        ((status = apr_procattr_child_in_set(procattr,
                                             pl->read_fd,
                                             pl->write_fd))
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

        apr_tokenize_to_argv(pl->program, &args, pl->p);
        pname = apr_pstrdup(pl->p, args[0]);
        procnew = apr_pcalloc(pl->p, sizeof(apr_proc_t));
        status = apr_proc_create(procnew, pname, (const char * const *) args,
                                 NULL, procattr, pl->p);

        if (status == APR_SUCCESS) {
            pl->pid = procnew;
            /* procnew->in was dup2'd from pl->write_fd;
             * since the original fd is still valid, close the copy to
             * avoid a leak. */
            apr_file_close(procnew->in);
            procnew->in = NULL;
            apr_proc_other_child_register(procnew, piped_log_maintenance, pl,
                                          pl->write_fd, pl->p);
            close_handle_in_child(pl->p, pl->read_fd);
        }
        else {
            char buf[120];
            /* Something bad happened, give up and go away. */
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00104)
                         "unable to start piped log program '%s': %s",
                         pl->program, apr_strerror(status, buf, sizeof(buf)));
        }
    }

    return status;
}