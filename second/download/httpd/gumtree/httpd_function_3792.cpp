static apr_status_t include_cmd(include_ctx_t *ctx, ap_filter_t *f,
                                apr_bucket_brigade *bb, const char *command)
{
    cgi_exec_info_t  e_info;
    const char **argv;
    apr_file_t *script_out = NULL, *script_in = NULL, *script_err = NULL;
    apr_status_t rv;
    request_rec *r = f->r;

    add_ssi_vars(r);

    e_info.process_cgi = 0;
    e_info.cmd_type    = APR_SHELLCMD;
    e_info.detached    = 0;
    e_info.in_pipe     = APR_NO_PIPE;
    e_info.out_pipe    = APR_FULL_BLOCK;
    e_info.err_pipe    = APR_NO_PIPE;
    e_info.prog_type   = RUN_AS_SSI;
    e_info.bb          = &bb;
    e_info.ctx         = ctx;
    e_info.next        = f->next;
    e_info.addrspace   = 0;

    if ((rv = cgi_build_command(&command, &argv, r, r->pool,
                                &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "don't know how to spawn cmd child process: %s",
                      r->filename);
        return rv;
    }

    /* run the script in its own process */
    if ((rv = run_cgi_child(&script_out, &script_in, &script_err,
                            command, argv, r, r->pool,
                            &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "couldn't spawn child process: %s", r->filename);
        return rv;
    }

    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pipe_create(script_in,
                            f->c->bucket_alloc));
    ctx->flush_now = 1;

    /* We can't close the pipe here, because we may return before the
     * full CGI has been sent to the network.  That's okay though,
     * because we can rely on the pool to close the pipe for us.
     */
    return APR_SUCCESS;
}