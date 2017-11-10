static int log_child(apr_pool_t *p, const char *progname,
                     apr_file_t **fpin, apr_cmdtype_e cmdtype,
                     int dummy_stderr)
{
    /* Child process code for 'ErrorLog "|..."';
     * may want a common framework for this, since I expect it will
     * be common for other foo-loggers to want this sort of thing...
     */
    apr_status_t rc;
    apr_procattr_t *procattr;
    apr_proc_t *procnew;
    apr_file_t *errfile;

    if (((rc = apr_procattr_create(&procattr, p)) == APR_SUCCESS)
        && ((rc = apr_procattr_dir_set(procattr,
                                       ap_server_root)) == APR_SUCCESS)
        && ((rc = apr_procattr_cmdtype_set(procattr, cmdtype)) == APR_SUCCESS)
        && ((rc = apr_procattr_io_set(procattr,
                                      APR_FULL_BLOCK,
                                      APR_NO_PIPE,
                                      APR_NO_PIPE)) == APR_SUCCESS)
        && ((rc = apr_procattr_error_check_set(procattr, 1)) == APR_SUCCESS)
        && ((rc = apr_procattr_child_errfn_set(procattr, log_child_errfn)) 
                == APR_SUCCESS)) {
        char **args;
        const char *pname;

        apr_tokenize_to_argv(progname, &args, p);
        pname = apr_pstrdup(p, args[0]);
        procnew = (apr_proc_t *)apr_pcalloc(p, sizeof(*procnew));

        if (dummy_stderr) {
            if ((rc = apr_file_open_stdout(&errfile, p)) == APR_SUCCESS)
                rc = apr_procattr_child_err_set(procattr, errfile, NULL);
        }

        rc = apr_proc_create(procnew, pname, (const char * const *)args,
                             NULL, procattr, p);

        if (rc == APR_SUCCESS) {
            apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);
            (*fpin) = procnew->in;
            /* read handle to pipe not kept open, so no need to call
             * close_handle_in_child()
             */
        }
    }

    return rc;
}