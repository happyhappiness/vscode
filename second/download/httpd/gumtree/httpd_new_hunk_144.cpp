}


static int include_cmd(include_ctx_t *ctx, apr_bucket_brigade **bb,
                       const char *command, request_rec *r, ap_filter_t *f)
{
    cgi_exec_info_t  e_info;
    const char   **argv;
    apr_file_t    *script_out = NULL, *script_in = NULL, *script_err = NULL;
    apr_bucket_brigade *bcgi;
    apr_bucket *b;
    apr_status_t rv;

    e_info.process_cgi = 0;
    e_info.cmd_type    = APR_SHELLCMD;
    e_info.detached    = 0;
    e_info.in_pipe     = APR_NO_PIPE;
    e_info.out_pipe    = APR_FULL_BLOCK;
    e_info.err_pipe    = APR_NO_PIPE;
    e_info.prog_type   = RUN_AS_SSI;
    e_info.bb          = bb;
    e_info.ctx         = ctx;
    e_info.next        = f->next;

    if ((rv = cgi_build_command(&command, &argv, r, r->pool, &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "don't know how to spawn cmd child process: %s", 
                      r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* run the script in its own process */
    if ((rv = run_cgi_child(&script_out, &script_in, &script_err,
                            command, argv, r, r->pool,
                            &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "couldn't spawn child process: %s", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    bcgi = apr_brigade_create(r->pool, f->c->bucket_alloc);
