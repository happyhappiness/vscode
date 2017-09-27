    e_info.ctx         = NULL;
    e_info.next        = NULL;
    e_info.addrspace   = 0;

    /* build the command line */
    if ((rv = cgi_build_command(&command, &argv, r, p, &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01222)
                      "don't know how to spawn child process: %s",
                      r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* run the script in its own process */
    if ((rv = run_cgi_child(&script_out, &script_in, &script_err,
                            command, argv, r, p, &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01223)
                      "couldn't spawn child process: %s", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* Transfer any put/post args, CERN style...
     * Note that we already ignore SIGPIPE in the core server.
