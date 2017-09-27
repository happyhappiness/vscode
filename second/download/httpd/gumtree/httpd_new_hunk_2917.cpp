        (apr_procattr_io_set(procattr, APR_FULL_BLOCK,
                           APR_FULL_BLOCK, APR_NO_PIPE)   != APR_SUCCESS) ||
        (apr_procattr_dir_set(procattr,
                              ap_make_dirstr_parent(r->pool, r->filename)) != APR_SUCCESS) ||
        (apr_procattr_cmdtype_set(procattr, APR_PROGRAM_PATH) != APR_SUCCESS)) {
        /* Something bad happened, tell the world. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_ENOPROC, r, APLOGNO(01551)
               "couldn't setup child process: %s", r->filename);
    }
    else {
        new_argv[0] = compr[parm->method].argv[0];
        new_argv[1] = compr[parm->method].argv[1];
        new_argv[2] = r->filename;
