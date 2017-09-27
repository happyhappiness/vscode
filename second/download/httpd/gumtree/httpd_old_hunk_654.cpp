                                      conf->limit_nproc)) != APR_SUCCESS) ||
#endif
        ((rc = apr_procattr_cmdtype_set(procattr,
                                        e_info->cmd_type)) != APR_SUCCESS) ||

        ((rc = apr_procattr_detach_set(procattr,
                                        e_info->detached & AP_PROC_DETACHED)) != APR_SUCCESS) ||
        ((rc = apr_procattr_addrspace_set(procattr,
                                        (e_info->detached & AP_PROC_NEWADDRSPACE) ? 1 : 0)) != APR_SUCCESS) ||
        ((rc = apr_procattr_child_errfn_set(procattr, cgi_child_errfn)) != APR_SUCCESS)) {
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
            ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, rc, r,
                          "couldn't create child process: %d: %s", rc,
                          apr_filename_of_pathname(r->filename));
        }
        else {
            apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);

            *script_in = procnew->out;
            if (!*script_in)
