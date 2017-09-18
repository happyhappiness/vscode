     */
    if ((*conf->xbithack != xbithack_full)
        || !(f->r->finfo.valid & APR_FINFO_GPROT)
        || !(f->r->finfo.protection & APR_GEXECUTE)) {
        f->r->no_local_copy = 1;
    }
    
    return OK;
}

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
