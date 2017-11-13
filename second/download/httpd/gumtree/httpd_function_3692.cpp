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
        const char *ctypes;

        if (ctx->filter->mode == INPUT_FILTER) {
            ctypes = apr_table_get(f->r->headers_in, "Content-Type");
        }
        else {
            ctypes = f->r->content_type;
        }

        if (ctypes) {
            const char *ctype = ap_getword(f->r->pool, &ctypes, ';');

            if (strcasecmp(ctx->filter->intype, ctype)) {
                /* wrong IMT for us; don't mess with the output */
                ctx->noop = 1;
            }
        }
        else {
            ctx->noop = 1;
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
            ap_set_content_type(f->r, ctx->filter->outtype);
        }
        if (ctx->filter->preserves_content_length != 1) {
            /* nasty, but needed to avoid confusing the browser
             */
            apr_table_unset(f->r->headers_out, "Content-Length");
        }
    }

    if (dc->debug >= DBGLVL_SHOWOPTIONS) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                      "%sfiltering `%s' of type `%s' through `%s', cfg %s",
                      ctx->noop ? "NOT " : "",
                      f->r->uri ? f->r->uri : f->r->filename,
                      f->r->content_type ? f->r->content_type : "(unspecified)",
                      ctx->filter->command,
                      get_cfg_string(dc, ctx->filter, f->r->pool));
    }

    return APR_SUCCESS;
}