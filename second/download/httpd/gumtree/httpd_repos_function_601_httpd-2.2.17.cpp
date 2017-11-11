static apr_status_t ssl_pipe_child_create(apr_pool_t *p, const char *progname)
{
    /* Child process code for 'ErrorLog "|..."';
     * may want a common framework for this, since I expect it will
     * be common for other foo-loggers to want this sort of thing...
     */
    apr_status_t rc;
    apr_procattr_t *procattr;
    apr_proc_t *procnew;

    if (((rc = apr_procattr_create(&procattr, p)) == APR_SUCCESS) &&
        ((rc = apr_procattr_io_set(procattr,
                                   APR_FULL_BLOCK,
                                   APR_FULL_BLOCK,
                                   APR_NO_PIPE)) == APR_SUCCESS)) {
        char **args;
        const char *pname;

        apr_tokenize_to_argv(progname, &args, p);
        pname = apr_pstrdup(p, args[0]);
        procnew = (apr_proc_t *)apr_pcalloc(p, sizeof(*procnew));
        rc = apr_proc_create(procnew, pname, (const char * const *)args,
                             NULL, procattr, p);
        if (rc == APR_SUCCESS) {
            /* XXX: not sure if we aught to...
             * apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);
             */
            writetty = procnew->in;
            readtty = procnew->out;
        }
    }

    return rc;
}