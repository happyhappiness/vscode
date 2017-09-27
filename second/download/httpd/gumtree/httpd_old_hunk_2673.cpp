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
