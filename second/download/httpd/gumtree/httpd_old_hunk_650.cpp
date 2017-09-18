                        "ExtFilterOptions %s %s %s ExtFilterInType %s "
                        "ExtFilterOuttype %s",
                        debug_str, log_stderr_str, preserve_content_length_str,
                        intype_str, outtype_str);
}

static apr_status_t init_filter_instance(ap_filter_t *f)
{
    ef_ctx_t *ctx;
    ef_dir_t *dc;
    ef_server_t *sc;
    apr_status_t rv;

    f->ctx = ctx = apr_pcalloc(f->r->pool, sizeof(ef_ctx_t));
    dc = ap_get_module_config(f->r->per_dir_config,
                              &ext_filter_module);
    sc = ap_get_module_config(f->r->server->module_config,
                              &ext_filter_module);
    ctx->dc = dc;
    /* look for the user-defined filter */
    ctx->filter = apr_hash_get(sc->h, f->frec->name, APR_HASH_KEY_STRING);
    if (!ctx->filter) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                      "couldn't find definition of filter '%s'",
                      f->frec->name);
        return APR_EINVAL;
    }
    ctx->p = f->r->pool;
    if (ctx->filter->intype &&
        ctx->filter->intype != INTYPE_ALL &&
        strcasecmp(ctx->filter->intype, f->r->content_type)) {
        /* wrong IMT for us; don't mess with the output */
        ctx->noop = 1;
    }
    else {
        rv = init_ext_filter_process(f);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (ctx->filter->outtype &&
            ctx->filter->outtype != OUTTYPE_UNCHANGED) {
