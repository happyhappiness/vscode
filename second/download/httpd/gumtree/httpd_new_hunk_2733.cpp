    e_info.ctx         = ctx;
    e_info.next        = f->next;
    e_info.addrspace   = 0;

    if ((rv = cgi_build_command(&command, &argv, r, r->pool,
                                &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01226)
                      "don't know how to spawn cmd child process: %s",
                      r->filename);
        return rv;
    }

    /* run the script in its own process */
    if ((rv = run_cgi_child(&script_out, &script_in, &script_err,
                            command, argv, r, r->pool,
                            &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01227)
                      "couldn't spawn child process: %s", r->filename);
        return rv;
    }

    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pipe_create(script_in,
                            f->c->bucket_alloc));
