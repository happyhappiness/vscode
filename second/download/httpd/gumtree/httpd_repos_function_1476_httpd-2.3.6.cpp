static apr_status_t run_cgi_child(apr_file_t **script_out,
                                  apr_file_t **script_in,
                                  apr_file_t **script_err,
                                  const char *command,
                                  const char * const argv[],
                                  request_rec *r,
                                  apr_pool_t *p,
                                  cgi_exec_info_t *e_info)
{
    const char * const *env;
    apr_procattr_t *procattr;
    apr_proc_t *procnew;
    apr_status_t rc = APR_SUCCESS;

#if defined(RLIMIT_CPU)  || defined(RLIMIT_NPROC) || \
    defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined (RLIMIT_AS)

    core_dir_config *conf = ap_get_module_config(r->per_dir_config,
                                                 &core_module);
#endif

#ifdef DEBUG_CGI
#ifdef OS2
    /* Under OS/2 need to use device con. */
    FILE *dbg = fopen("con", "w");
#else
    FILE *dbg = fopen("/dev/tty", "w");
#endif
    int i;
#endif

    RAISE_SIGSTOP(CGI_CHILD);
#ifdef DEBUG_CGI
    fprintf(dbg, "Attempting to exec %s as CGI child (argv0 = %s)\n",
            r->filename, argv[0]);
#endif

    env = (const char * const *)ap_create_environment(p, r->subprocess_env);

#ifdef DEBUG_CGI
    fprintf(dbg, "Environment: \n");
    for (i = 0; env[i]; ++i)
        fprintf(dbg, "'%s'\n", env[i]);
    fclose(dbg);
#endif

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
                                        e_info->detached)) != APR_SUCCESS) ||
        ((rc = apr_procattr_addrspace_set(procattr,
                                        e_info->addrspace)) != APR_SUCCESS) ||
        ((rc = apr_procattr_child_errfn_set(procattr, cgi_child_errfn)) != APR_SUCCESS)) {
        /* Something bad happened, tell the world. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                      "couldn't set child process attributes: %s", r->filename);
    }
    else {
        procnew = apr_pcalloc(p, sizeof(*procnew));
        rc = ap_os_create_privileged_process(r, procnew, command, argv, env,
                                             procattr, p);

        if (rc != APR_SUCCESS) {
            /* Bad things happened. Everyone should have cleaned up. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, rc, r,
                          "couldn't create child process: %d: %s", rc,
                          apr_filepath_name_get(r->filename));
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
    return (rc);
}