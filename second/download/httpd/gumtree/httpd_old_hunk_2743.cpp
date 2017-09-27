              ((rc = apr_procattr_child_err_set(procattr, r->server->error_log, NULL)) != APR_SUCCESS) ||
              ((rc = apr_procattr_child_in_set(procattr, inout, NULL)) != APR_SUCCESS))) ||
            ((rc = apr_procattr_child_out_set(procattr, inout, NULL)) != APR_SUCCESS) ||
            ((rc = apr_procattr_dir_set(procattr,
                                  ap_make_dirstr_parent(r->pool, r->filename))) != APR_SUCCESS) ||
            ((rc = apr_procattr_cmdtype_set(procattr, cmd_type)) != APR_SUCCESS) ||
            ((rc = apr_procattr_child_errfn_set(procattr, cgid_child_errfn)) != APR_SUCCESS)) {
            /* Something bad happened, tell the world.
             * ap_log_rerror() won't work because the header table used by
             * ap_log_rerror() hasn't been replicated in the phony r
             */
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
                         "couldn't set child process attributes: %s", r->filename);

            procnew->pid = 0; /* no process to clean up */
            close(sd2);
        }
        else {
