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
