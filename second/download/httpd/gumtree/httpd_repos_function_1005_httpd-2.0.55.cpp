static apr_status_t rewritemap_program_child(apr_pool_t *p,
                                             const char *progname, char **argv,
                                             apr_file_t **fpout,
                                             apr_file_t **fpin)
{
    apr_status_t rc;
    apr_procattr_t *procattr;
    apr_proc_t *procnew;

    if (((rc = apr_procattr_create(&procattr, p)) != APR_SUCCESS) ||
        ((rc = apr_procattr_io_set(procattr, APR_FULL_BLOCK, APR_FULL_BLOCK,
                                   APR_NO_PIPE)) != APR_SUCCESS) ||
        ((rc = apr_procattr_dir_set(procattr,
                                   ap_make_dirstr_parent(p, argv[0])))
         != APR_SUCCESS) ||
        ((rc = apr_procattr_cmdtype_set(procattr, APR_PROGRAM))
         != APR_SUCCESS)) {
        /* Something bad happened, give up and go away. */
    }
    else {
        procnew = apr_pcalloc(p, sizeof(*procnew));
        rc = apr_proc_create(procnew, argv[0], (const char **)argv, NULL,
                             procattr, p);

        if (rc == APR_SUCCESS) {
            apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);

            if (fpin) {
                (*fpin) = procnew->in;
            }

            if (fpout) {
                (*fpout) = procnew->out;
            }
        }
    }

    return (rc);
}