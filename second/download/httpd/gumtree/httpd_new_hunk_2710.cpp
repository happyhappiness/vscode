    }

    /* Don't allow ETag headers to be generated - see RFC2616 - 13.3.4.
     * We don't know if we are going to be including a file or executing
     * a program - in either case a strong ETag header will likely be invalid.
     */
    if (conf->etag <= 0) {
        apr_table_setn(f->r->notes, "no-etag", "");
    }

    return OK;
}

static apr_status_t includes_filter(ap_filter_t *f, apr_bucket_brigade *b)
{
    request_rec *r = f->r;
    request_rec *parent;
    include_dir_config *conf = ap_get_module_config(r->per_dir_config,
                                                    &include_module);

    include_server_config *sconf= ap_get_module_config(r->server->module_config,
                                                       &include_module);

    if (!(ap_allow_options(r) & OPT_INCLUDES)) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01374)
                      "mod_include: Options +Includes (or IncludesNoExec) "
                      "wasn't set, INCLUDES filter removed");
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, b);
    }

    if (!f->ctx) {
        struct ssi_internal_ctx *intern;
        include_ctx_t *ctx;

        /* create context for this filter */
        f->ctx = ctx = apr_palloc(r->pool, sizeof(*ctx));
        ctx->r = r;
        ctx->intern = intern = apr_palloc(r->pool, sizeof(*ctx->intern));
        ctx->pool = r->pool;
        apr_pool_create(&ctx->dpool, ctx->pool);

        /* runtime data */
        intern->tmp_bb = apr_brigade_create(ctx->pool, f->c->bucket_alloc);
        intern->seen_eos = 0;
        intern->state = PARSE_PRE_HEAD;
        ctx->flags = (SSI_FLAG_PRINTING | SSI_FLAG_COND_TRUE);
        if ((ap_allow_options(r) & OPT_INC_WITH_EXEC) == 0) {
            ctx->flags |= SSI_FLAG_NO_EXEC;
        }
        intern->legacy_expr = (conf->legacy_expr > 0);
        intern->expr_eval_ctx = NULL;
        intern->expr_err = NULL;
        intern->expr_vary_this = NULL;

        ctx->if_nesting_level = 0;
        intern->re = NULL;

        ctx->error_str = conf->default_error_msg ? conf->default_error_msg :
                         DEFAULT_ERROR_MSG;
        ctx->time_str = conf->default_time_fmt ? conf->default_time_fmt :
                        DEFAULT_TIME_FORMAT;
        intern->start_seq  = sconf->default_start_tag;
        intern->start_seq_pat = bndm_compile(ctx->pool, intern->start_seq,
                                             strlen(intern->start_seq));
        intern->end_seq = sconf->default_end_tag;
        intern->end_seq_len = strlen(intern->end_seq);
        intern->undefined_echo = conf->undefined_echo ? conf->undefined_echo :
                                 DEFAULT_UNDEFINED_ECHO;
        intern->undefined_echo_len = strlen(intern->undefined_echo);
    }

    if ((parent = ap_get_module_config(r->request_config, &include_module))) {
        /* Kludge --- for nested includes, we want to keep the subprocess
         * environment of the base document (for compatibility); that means
         * torquing our own last_modified date as well so that the
         * LAST_MODIFIED variable gets reset to the proper value if the
         * nested document resets <!--#config timefmt -->.
         */
