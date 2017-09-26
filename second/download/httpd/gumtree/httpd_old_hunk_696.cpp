    return OK;
}

static apr_status_t includes_filter(ap_filter_t *f, apr_bucket_brigade *b)
{
    request_rec *r = f->r;
    ssi_ctx_t *ctx = f->ctx;
    request_rec *parent;
    include_dir_config *conf = 
                   (include_dir_config *)ap_get_module_config(r->per_dir_config,
                                                              &include_module);

    include_server_config *sconf= ap_get_module_config(r->server->module_config,
                                                              &include_module);

    if (!(ap_allow_options(r) & OPT_INCLUDES)) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                      "mod_include: Options +Includes (or IncludesNoExec) "
                      "wasn't set, INCLUDES filter removed");
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, b);
    }

    if (!f->ctx) {
        /* create context for this filter */
        f->ctx = ctx = apr_palloc(f->c->pool, sizeof(*ctx));
        ctx->ctx = apr_pcalloc(f->c->pool, sizeof(*ctx->ctx));
        ctx->ctx->pool = f->r->pool;
        apr_pool_create(&ctx->dpool, ctx->ctx->pool);

        /* configuration data */
        ctx->end_seq_len = strlen(sconf->default_end_tag);
        ctx->r = f->r;

        /* runtime data */
        ctx->tmp_bb = apr_brigade_create(ctx->ctx->pool, f->c->bucket_alloc);
        ctx->seen_eos = 0;
        ctx->state = PARSE_PRE_HEAD;
        ctx->ctx->flags = (FLAG_PRINTING | FLAG_COND_TRUE);
        if (ap_allow_options(f->r) & OPT_INCNOEXEC) {
            ctx->ctx->flags |= FLAG_NO_EXEC;
        }
        ctx->ctx->if_nesting_level = 0;
        ctx->ctx->re_string = NULL;
        ctx->ctx->error_str_override = NULL;
        ctx->ctx->time_str_override = NULL;

        ctx->ctx->error_str = conf->default_error_msg;
        ctx->ctx->time_str = conf->default_time_fmt;
        ctx->ctx->start_seq_pat = &sconf->start_seq_pat;
        ctx->ctx->start_seq  = sconf->default_start_tag;
        ctx->ctx->start_seq_len = sconf->start_tag_len;
        ctx->ctx->end_seq = sconf->default_end_tag;

        /* legacy compat stuff */
        ctx->ctx->state = PARSED; /* dummy */
        ctx->ctx->ssi_tag_brigade = apr_brigade_create(f->c->pool,
                                                       f->c->bucket_alloc);
        ctx->ctx->status = APR_SUCCESS;
        ctx->ctx->head_start_index = 0;
        ctx->ctx->tag_start_index = 0;
        ctx->ctx->tail_start_index = 0;
    }
    else {
        ctx->ctx->bytes_parsed = 0;
    }

    if ((parent = ap_get_module_config(r->request_config, &include_module))) {
        /* Kludge --- for nested includes, we want to keep the subprocess
         * environment of the base document (for compatibility); that means
         * torquing our own last_modified date as well so that the
