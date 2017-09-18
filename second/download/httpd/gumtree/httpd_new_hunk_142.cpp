
    /* Transmute ourselves into the script.
     * NB only ISINDEX scripts get decoded arguments.
     */
    if (((rc = apr_procattr_create(&procattr, p)) != APR_SUCCESS) ||
        ((rc = apr_procattr_io_set(procattr,
                                   e_info->in_pipe,
                                   e_info->out_pipe,
                                   e_info->err_pipe)) != APR_SUCCESS) ||
        ((rc = apr_procattr_dir_set(procattr, 
                        ap_make_dirstr_parent(r->pool,
                                              r->filename))) != APR_SUCCESS) ||
#ifdef RLIMIT_CPU
        ((rc = apr_procattr_limit_set(procattr, APR_LIMIT_CPU,
                                      conf->limit_cpu)) != APR_SUCCESS) ||
#endif
#if defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS)
        ((rc = apr_procattr_limit_set(procattr, APR_LIMIT_MEM,
                                      conf->limit_mem)) != APR_SUCCESS) ||
#endif
#ifdef RLIMIT_NPROC
        ((rc = apr_procattr_limit_set(procattr, APR_LIMIT_NPROC,
                                      conf->limit_nproc)) != APR_SUCCESS) ||
#endif
        ((rc = apr_procattr_cmdtype_set(procattr,
                                        e_info->cmd_type)) != APR_SUCCESS) ||

        ((rc = apr_procattr_detach_set(procattr,
                                        e_info->detached)) != APR_SUCCESS)) {
        /* Something bad happened, tell the world. */
	ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
		      "couldn't set child process attributes: %s", r->filename);
    }
    else {
        procnew = apr_pcalloc(p, sizeof(*procnew));
        if (e_info->prog_type == RUN_AS_SSI) {
            SPLIT_AND_PASS_PRETAG_BUCKETS(*(e_info->bb), e_info->ctx,
                                          e_info->next, rc);
            if (rc != APR_SUCCESS) {
                return rc;
            }
        }

        rc = ap_os_create_privileged_process(r, procnew, command, argv, env,
                                             procattr, p);
    
        if (rc != APR_SUCCESS) {
            /* Bad things happened. Everyone should have cleaned up. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                          "couldn't create child process: %d: %s", rc,
                          r->filename);
        }
        else {
            apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);

            *script_in = procnew->out;
            if (!*script_in)
                return APR_EBADF;
            apr_file_pipe_timeout_set(*script_in, r->server->timeout);

            if (e_info->prog_type == RUN_AS_CGI) {
                *script_out = procnew->in;
                if (!*script_out)
                    return APR_EBADF;
                apr_file_pipe_timeout_set(*script_out, r->server->timeout);

                *script_err = procnew->err;
                if (!*script_err)
                    return APR_EBADF;
                apr_file_pipe_timeout_set(*script_err, r->server->timeout);
            }
        }
    }
#ifdef DEBUG_CGI
    fclose(dbg);
#endif
    return (rc);
}


static apr_status_t default_build_command(const char **cmd, const char ***argv,
                                          request_rec *r, apr_pool_t *p,
                                          cgi_exec_info_t *e_info)
{
    int numwords, x, idx;
    char *w;
    const char *args = NULL;

    if (e_info->process_cgi) {
        /* Allow suexec's "/" check to succeed */
        const char *argv0 = strrchr(r->filename, '/');
        if (argv0 != NULL)
            argv0++;
        else
            argv0 = r->filename;
