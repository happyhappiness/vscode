    const char *const *env;
    request_rec *r = parm->r;
    apr_pool_t *child_context = cntxt;
    apr_procattr_t *procattr;
    apr_proc_t *procnew;

    /* XXX missing 1.3 logic: 
     *
     * what happens when !compr[parm->method].silent?
     * Should we create the err pipe, read it, and copy to the log?
     */
        
    env = (const char *const *)ap_create_environment(child_context, r->subprocess_env);

    if ((apr_procattr_create(&procattr, child_context) != APR_SUCCESS) ||
        (apr_procattr_io_set(procattr, APR_FULL_BLOCK, 
                           APR_FULL_BLOCK, APR_NO_PIPE)   != APR_SUCCESS) ||
        (apr_procattr_dir_set(procattr, r->filename)        != APR_SUCCESS) ||
        (apr_procattr_cmdtype_set(procattr, APR_PROGRAM)    != APR_SUCCESS)) {
        /* Something bad happened, tell the world. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_ENOPROC, r,
               "couldn't setup child process: %s", r->filename);
