static apr_status_t sed_request_filter(ap_filter_t *f,
                                       apr_bucket_brigade *bb,
                                       ap_input_mode_t mode,
                                       apr_read_type_e block,
                                       apr_off_t readbytes)
{
    sed_config *cfg = ap_get_module_config(f->r->per_dir_config,
                                           &sed_module);
    sed_filter_ctxt *ctx = f->ctx;
    apr_status_t status;
    apr_bucket_brigade *bbinp;
    sed_expr_config *sed_cfg = &cfg->input;

    if (mode != AP_MODE_READBYTES) {
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    if ((sed_cfg == NULL) || (sed_cfg->sed_cmds == NULL)) {
        /* No sed expression */
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    if (!ctx) {
        if (!ap_is_initial_req(f->r)) {
            ap_remove_input_filter(f);
            /* XXX : Should we filter the sub requests too */
            return ap_get_brigade(f->next, bb, mode, block, readbytes);
        }
        status = init_context(f, sed_cfg, 0);
        if (status != APR_SUCCESS)
             return status;
        ctx = f->ctx;
        ctx->bb    = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
        ctx->bbinp = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
    }

    bbinp = ctx->bbinp;

    /* Here is the logic :
     * Read the readbytes data from next level fiter into bbinp. Loop through
     * the buckets in bbinp and read the data from buckets and invoke
     * sed_eval_buffer on the data. libsed will generate its output using
     * sed_write_output which will add data in ctx->bb. Do it until it have
     * atleast one bucket bucket in ctx->bb. At the end of data eos bucket
     * should be there.
     *
     * Once eos bucket is seen, then invoke sed_finalize_eval to clear the
     * output. If the last byte of data is not a new line character then sed
     * will add a new line to the data that is default sed behaviour. Note
     * that using this filter with POST data, caller may not expect this
     * behaviour.
     *
     * If next level fiter generate the flush bucket, we can't do much about
     * it. If we want to return the flush bucket in brigade bb (to the caller)
     * the question is where to add it?
     */
    while (APR_BRIGADE_EMPTY(ctx->bb)) {
        apr_bucket *b;

        /* read the bytes from next level filter */
        apr_brigade_cleanup(bbinp);
        status = ap_get_brigade(f->next, bbinp, mode, block, readbytes);
        if (status != APR_SUCCESS) {
            return status;
        }
        for (b = APR_BRIGADE_FIRST(bbinp); b != APR_BRIGADE_SENTINEL(bbinp);
             b = APR_BUCKET_NEXT(b)) {
            const char *buf = NULL;
            apr_size_t bytes;

            if (APR_BUCKET_IS_EOS(b)) {
                /* eos bucket. Clear the internal sed buffers */
                sed_finalize_eval(&ctx->eval, ctx);
                flush_output_buffer(ctx);
                APR_BUCKET_REMOVE(b);
                APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
                break;
            }
            else if (APR_BUCKET_IS_FLUSH(b)) {
                /* What should we do with flush bucket */
                continue;
            }
            if (apr_bucket_read(b, &buf, &bytes, APR_BLOCK_READ)
                     == APR_SUCCESS) {
                status = sed_eval_buffer(&ctx->eval, buf, bytes, ctx);
                if (status != APR_SUCCESS)
                    return status;
                flush_output_buffer(ctx);
            }
        }
    }

    if (!APR_BRIGADE_EMPTY(ctx->bb)) {
        apr_bucket *b = NULL;

        if (apr_brigade_partition(ctx->bb, readbytes, &b) == APR_INCOMPLETE) {
            APR_BRIGADE_CONCAT(bb, ctx->bb);
        }
        else {
            APR_BRIGADE_CONCAT(bb, ctx->bb);
            apr_brigade_split_ex(bb, b, ctx->bb);
        }
    }
    return APR_SUCCESS;
}