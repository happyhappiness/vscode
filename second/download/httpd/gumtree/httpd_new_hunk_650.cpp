                        "ExtFilterOptions %s %s %s ExtFilterInType %s "
                        "ExtFilterOuttype %s",
                        debug_str, log_stderr_str, preserve_content_length_str,
                        intype_str, outtype_str);
}

static ef_filter_t *find_filter_def(const server_rec *s, const char *fname)
{
    ef_server_t *sc;
    ef_filter_t *f;

    sc = ap_get_module_config(s->module_config, &ext_filter_module);
    f = apr_hash_get(sc->h, fname, APR_HASH_KEY_STRING);
    if (!f && s != main_server) {
        s = main_server;
        sc = ap_get_module_config(s->module_config, &ext_filter_module);
        f = apr_hash_get(sc->h, fname, APR_HASH_KEY_STRING);
    }
    return f;
}

static apr_status_t init_filter_instance(ap_filter_t *f)
{
    ef_ctx_t *ctx;
    ef_dir_t *dc;
    apr_status_t rv;

    f->ctx = ctx = apr_pcalloc(f->r->pool, sizeof(ef_ctx_t));
    dc = ap_get_module_config(f->r->per_dir_config,
                              &ext_filter_module);
    ctx->dc = dc;
    /* look for the user-defined filter */
    ctx->filter = find_filter_def(f->r->server, f->frec->name);
    if (!ctx->filter) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                      "couldn't find definition of filter '%s'",
                      f->frec->name);
        return APR_EINVAL;
    }
    ctx->p = f->r->pool;
    if (ctx->filter->intype &&
        ctx->filter->intype != INTYPE_ALL) {
        if (!f->r->content_type) {
            ctx->noop = 1;
        }
        else {
            const char *ctypes = f->r->content_type;
            const char *ctype = ap_getword(f->r->pool, &ctypes, ';');

            if (strcasecmp(ctx->filter->intype, ctype)) {
                /* wrong IMT for us; don't mess with the output */
                ctx->noop = 1;
            }
        }
    }
    if (ctx->filter->enable_env &&
        !apr_table_get(f->r->subprocess_env, ctx->filter->enable_env)) {
        /* an environment variable that enables the filter isn't set; bail */
        ctx->noop = 1;
    }
    if (ctx->filter->disable_env &&
        apr_table_get(f->r->subprocess_env, ctx->filter->disable_env)) {
        /* an environment variable that disables the filter is set; bail */
        ctx->noop = 1;
    }
    if (!ctx->noop) {
        rv = init_ext_filter_process(f);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (ctx->filter->outtype &&
            ctx->filter->outtype != OUTTYPE_UNCHANGED) {
