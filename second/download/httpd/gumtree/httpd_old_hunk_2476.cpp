    }

    if (fork_req) {
       rv = apr_proc_fork(&proc, r->pool);
        switch (rv) {
        case APR_INPARENT:
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "parent waiting for child");
            /* FIXME - does the child need to run synchronously?
             * esp. if we enable mod_privileges with threaded MPMs?
             * We do need at least to ensure r outlives the child.
             */
            rv = apr_proc_wait(&proc, &exitcode, &exitwhy, APR_WAIT);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "parent: child %s",
                          (rv == APR_CHILD_DONE) ? "done" : "notdone");

            /* The child has taken responsibility for reading all input
             * and sending all output.  So we need to bow right out,
             * and even abandon "normal" housekeeping.
             */
