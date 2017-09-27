{
    apr_procattr_t *procattr;
    apr_proc_t *procnew = NULL;
    apr_status_t status;

    if (((status = apr_procattr_create(&procattr, pl->p)) != APR_SUCCESS) ||
        ((status = apr_procattr_cmdtype_set(procattr,
                                            APR_SHELLCMD_ENV)) != APR_SUCCESS) ||
        ((status = apr_procattr_child_in_set(procattr,
                                             ap_piped_log_read_fd(pl),
                                             ap_piped_log_write_fd(pl)))
        != APR_SUCCESS) ||
        ((status = apr_procattr_child_errfn_set(procattr, log_child_errfn))
         != APR_SUCCESS) ||
        ((status = apr_procattr_error_check_set(procattr, 1)) != APR_SUCCESS)) {
        char buf[120];
        /* Something bad happened, give up and go away. */
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
