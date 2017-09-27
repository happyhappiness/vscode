        procnew = apr_pcalloc(p, sizeof(*procnew));
        rc = ap_os_create_privileged_process(r, procnew, command, argv, env,
                                             procattr, p);

        if (rc != APR_SUCCESS) {
            /* Bad things happened. Everyone should have cleaned up. */
            /* Intentional no APLOGNO */
            ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, rc, r,
                          "couldn't create child process: %d: %s", rc,
                          apr_filepath_name_get(r->filename));
        }
        else {
            apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);
