static int privileges_req(request_rec *r)
{
    /* secure mode: fork a process to handle the request */
    apr_proc_t proc;
    apr_status_t rv;
    int exitcode;
    apr_exit_why_e exitwhy;
    int fork_req;
    priv_cfg *cfg = ap_get_module_config(r->server->module_config,
                                         &privileges_module);

    void *breadcrumb = ap_get_module_config(r->request_config,
                                            &privileges_module);

    if (!breadcrumb) {
        /* first call: this is the vhost */
        fork_req = (cfg->mode == PRIV_SECURE);

        /* set breadcrumb */
        ap_set_module_config(r->request_config, &privileges_module, &cfg->mode);

        /* If we have per-dir config, defer doing anything */
        if ((cfg->mode == PRIV_SELECTIVE)) {
            /* Defer dropping privileges 'til we have a directory
             * context that'll tell us whether to fork.
             */
            return DECLINED;
        }
    }
    else {
        /* second call is for per-directory. */
        priv_dir_cfg *dcfg;
        if ((cfg->mode != PRIV_SELECTIVE)) {
            /* Our fate was already determined for the vhost -
             * nothing to do per-directory
             */
            return DECLINED;
        }
        dcfg = ap_get_module_config(r->per_dir_config, &privileges_module);
        fork_req = (dcfg->mode == PRIV_SECURE);
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
            r->eos_sent = 1;
            apr_table_unset(r->headers_in, "Content-Type");
            apr_table_unset(r->headers_in, "Content-Length");
            /* Testing with ab and 100k requests reveals no nasties
             * so I infer we're not leaking anything like memory
             * or file descriptors.  That's nice!
             */
            return DONE;
        case APR_INCHILD:
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "In child!");
            break;  /* now we'll drop privileges in the child */
        default:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Failed to fork secure child process!");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    /* OK, now drop privileges. */

    /* cleanup should happen even if something fails part-way through here */
    apr_pool_cleanup_register(r->pool, r, privileges_end_req,
                              apr_pool_cleanup_null);
    /* set user and group if configured */
    if (cfg->uid || cfg->gid) {
        if (setppriv(PRIV_ON, PRIV_EFFECTIVE, priv_setid) == -1) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "No privilege to set user/group");
        }
        /* if we should be able to set these but can't, it could be
         * a serious security issue.  Bail out rather than risk it!
         */
        if (cfg->uid && (setuid(cfg->uid) == -1)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Error setting userid");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        if (cfg->gid && (setgid(cfg->gid) == -1)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Error setting group");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }
    /* set vhost's privileges */
    if (setppriv(PRIV_SET, PRIV_EFFECTIVE, cfg->priv) == -1) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
                      "Error setting effective privileges");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* ... including those of any subprocesses */
    if (setppriv(PRIV_SET, PRIV_INHERITABLE, cfg->child_priv) == -1) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
                      "Error setting inheritable privileges");
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if (setppriv(PRIV_SET, PRIV_LIMIT, cfg->child_priv) == -1) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
                      "Error setting limit privileges");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* If we're in a child process, drop down PPERM too */
    if (fork_req) {
        if (setppriv(PRIV_SET, PRIV_PERMITTED, cfg->priv) == -1) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
                          "Error setting permitted privileges");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    return OK;
}