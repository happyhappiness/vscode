        procnew = apr_pcalloc(child_context, sizeof(*procnew));
        rc = apr_proc_create(procnew, compr[parm->method].argv[0],
                               new_argv, NULL, procattr, child_context);

        if (rc != APR_SUCCESS) {
            /* Bad things happened. Everyone should have cleaned up. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_ENOPROC, r,
                          MODNAME ": could not execute `%s'.",
                          compr[parm->method].argv[0]);
        }
        else {
            apr_pool_note_subprocess(child_context, procnew, APR_KILL_AFTER_TIMEOUT);
            *pipe_in = procnew->out;
