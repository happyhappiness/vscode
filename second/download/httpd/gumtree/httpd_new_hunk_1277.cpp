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
