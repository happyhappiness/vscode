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

    /* Always unset the Last-Modified field - see RFC2616 - 13.3.4.
     * We don't know if we are going to be including a file or executing
     * a program which may change the Last-Modified header or make the 
     * content completely dynamic.  Therefore, we can't support these
     * headers.
     * Exception: XBitHack full means we *should* set the Last-Modified field.
     */

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

    /* add QUERY stuff to env cause it ain't yet */
    if (r->args) {
        char *arg_copy = apr_pstrdup(r->pool, r->args);

        apr_table_setn(r->subprocess_env, "QUERY_STRING", r->args);
        ap_unescape_url(arg_copy);
        apr_table_setn(r->subprocess_env, "QUERY_STRING_UNESCAPED",
                  ap_escape_shell_cmd(r->pool, arg_copy));
    }

    return send_parsed_content(f, b);
}