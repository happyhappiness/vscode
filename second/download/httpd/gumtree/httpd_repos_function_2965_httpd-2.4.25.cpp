static apr_status_t ef_input_filter(ap_filter_t *f, apr_bucket_brigade *bb,
                                    ap_input_mode_t mode, apr_read_type_e block,
                                    apr_off_t readbytes)
{
    ef_ctx_t *ctx = f->ctx;
    apr_status_t rv;

    /* just get out of the way of things we don't want. */
    if (mode != AP_MODE_READBYTES) {
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    if (!ctx) {
        if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
            ctx = f->ctx;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(01470)
                          "can't initialise input filter %s: %s",
                          f->frec->name,
                          (ctx->dc->onfail == 1) ? "removing" : "aborting");
            ap_remove_input_filter(f);
            if (ctx->dc->onfail == 1) {
                return ap_get_brigade(f->next, bb, mode, block, readbytes);
            }
            else {
                f->r->status = HTTP_INTERNAL_SERVER_ERROR;
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
        ctx = f->ctx;
    }

    if (ctx->hit_eos) {
        /* Match behaviour of HTTP_IN if filter is re-invoked after
         * hitting EOS: give back another EOS. */
        apr_bucket *e = apr_bucket_eos_create(f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);
        return APR_SUCCESS;
    }

    if (ctx->noop) {
        ap_remove_input_filter(f);
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    rv = ap_get_brigade(f->next, bb, mode, block, readbytes);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = ef_unified_filter(f, bb);
    return rv;
}