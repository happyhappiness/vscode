static apr_status_t includes_filter(ap_filter_t *f, apr_bucket_brigade *b)
{
    request_rec *r = f->r;
    include_ctx_t *ctx = f->ctx;
    request_rec *parent;
    include_dir_config *conf = 
                   (include_dir_config *)ap_get_module_config(r->per_dir_config,
                                                              &include_module);

    include_server_config *sconf= ap_get_module_config(r->server->module_config,
                                                              &include_module);

    if (!(ap_allow_options(r) & OPT_INCLUDES)) {
        return ap_pass_brigade(f->next, b);
    }

    if (!f->ctx) {
        f->ctx = ctx = apr_pcalloc(f->c->pool, sizeof(*ctx));
        ctx->state = PRE_HEAD;
        ctx->flags = (FLAG_PRINTING | FLAG_COND_TRUE);
        if (ap_allow_options(r) & OPT_INCNOEXEC) {
            ctx->flags |= FLAG_NO_EXEC;
        }
        ctx->ssi_tag_brigade = apr_brigade_create(f->c->pool,
                                                  f->c->bucket_alloc);
        ctx->status = APR_SUCCESS;

        ctx->error_str = conf->default_error_msg;
        ctx->time_str = conf->default_time_fmt;
        ctx->pool = f->c->pool;
        ctx->start_seq_pat = &sconf->start_seq_pat;
        ctx->start_seq  = sconf->default_start_tag;
        ctx->start_seq_len = sconf->start_tag_len;
        ctx->end_seq = sconf->default_end_tag;
    }
    else {
        ctx->bytes_parsed = 0;
    }

    if ((parent = ap_get_module_config(r->request_config, &include_module))) {
        /* Kludge --- for nested includes, we want to keep the subprocess
         * environment of the base document (for compatibility); that means
         * torquing our own last_modified date as well so that the
         * LAST_MODIFIED variable gets reset to the proper value if the
         * nested document resets <!--#config timefmt -->.
         */
        r->subprocess_env = r->main->subprocess_env;
        apr_pool_join(r->main->pool, r->pool);
        r->finfo.mtime = r->main->finfo.mtime;
    }
    else {
        /* we're not a nested include, so we create an initial
         * environment */
        ap_add_common_vars(r);
        ap_add_cgi_vars(r);
        add_include_vars(r, conf->default_time_fmt);
    }
    /* Always unset the content-length.  There is no way to know if
     * the content will be modified at some point by send_parsed_content.
     * It is very possible for us to not find any content in the first
     * 9k of the file, but still have to modify the content of the file.
     * If we are going to pass the file through send_parsed_content, then
     * the content-length should just be unset.
     */
    apr_table_unset(f->r->headers_out, "Content-Length");

    /* Always unset the ETag/Last-Modified fields - see RFC2616 - 13.3.4.
     * We don't know if we are going to be including a file or executing
     * a program which may change the Last-Modified header or make the 
     * content completely dynamic.  Therefore, we can't support these
     * headers.
     * Exception: XBitHack full means we *should* set the Last-Modified field.
     */
    apr_table_unset(f->r->headers_out, "ETag");

    /* Assure the platform supports Group protections */
    if ((*conf->xbithack == xbithack_full)
        && (r->finfo.valid & APR_FINFO_GPROT)
        && (r->finfo.protection & APR_GEXECUTE)) {
        ap_update_mtime(r, r->finfo.mtime);
        ap_set_last_modified(r);
    }
    else {
        apr_table_unset(f->r->headers_out, "Last-Modified");
    }

    return send_parsed_content(&b, r, f);
}