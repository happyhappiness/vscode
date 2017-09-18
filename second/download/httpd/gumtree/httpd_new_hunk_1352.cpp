                            APR_OS_DEFAULT, p)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                     "%s: could not open error log file %s.",
                     ap_server_argv0, fname);
        return rc;
    }
    if (!stderr_pool) {
        /* This is safe provided we revert it when we are finished.
         * We don't manager the callers pool!
         */
        stderr_pool = p;
    }
    if ((rc = apr_file_open_stderr(&stderr_log, stderr_pool)) 
            == APR_SUCCESS) {
        apr_file_flush(stderr_log);
        if ((rc = apr_file_dup2(stderr_log, stderr_file, stderr_pool)) 
                == APR_SUCCESS) {
            apr_file_close(stderr_file);
            /*
             * You might ponder why stderr_pool should survive?
             * The trouble is, stderr_pool may have s_main->error_log,
             * so we aren't in a position to destory stderr_pool until
             * the next recycle.  There's also an apparent bug which 
             * is not; if some folk decided to call this function before 
             * the core open error logs hook, this pool won't survive.
             * Neither does the stderr logger, so this isn't a problem.
             */
        }
    }
    /* Revert, see above */
    if (stderr_pool == p)
        stderr_pool = NULL;

    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rc, NULL,
                     "unable to replace stderr with error log file");
    }
    return rc;
}

static void log_child_errfn(apr_pool_t *pool, apr_status_t err,
                            const char *description)
{
    ap_log_error(APLOG_MARK, APLOG_ERR, err, NULL,
                 "%s", description);
}

/* Create a child process running PROGNAME with a pipe connected to
 * the childs stdin.  The write-end of the pipe will be placed in
 * *FPIN on successful return.  If dummy_stderr is non-zero, the
 * stderr for the child will be the same as the stdout of the parent.
 * Otherwise the child will inherit the stderr from the parent. */
static int log_child(apr_pool_t *p, const char *progname,
                     apr_file_t **fpin, int dummy_stderr)
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
