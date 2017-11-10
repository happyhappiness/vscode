static apr_status_t sed_response_filter(ap_filter_t *f,
                                        apr_bucket_brigade *bb)
{
    apr_bucket *b;
    apr_status_t status;
    sed_config *cfg = ap_get_module_config(f->r->per_dir_config,
                                           &sed_module);
    sed_filter_ctxt *ctx = f->ctx;
    sed_expr_config *sed_cfg = &cfg->output;

    if ((sed_cfg == NULL) || (sed_cfg->sed_cmds == NULL)) {
        /* No sed expressions */
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb);
    }

    if (ctx == NULL) {

        if (APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(bb))) {
            /* no need to run sed filter for Head requests */
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        status = init_context(f, sed_cfg, 1);
        if (status != APR_SUCCESS)
             return status;
        ctx = f->ctx;
        apr_table_unset(f->r->headers_out, "Content-Length");
    }

    ctx->bb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);

    /* Here is the main logic. Iterate through all the buckets, read the
     * content of the bucket, call sed_eval_buffer on the data.
     * sed_eval_buffer will read the data line by line, run filters on each
     * line. sed_eval_buffer will generates the output by calling
     * sed_write_output which will add the output to ctx->bb. At the end of
     * the loop, ctx->bb is passed to the next filter in chain. At the end of
     * the data, if new line is not found then sed_eval_buffer will store the
     * data in its own buffer.
     *
     * Once eos bucket is found then sed_finalize_eval will flush the rest of
     * the data. If there is no new line in last line of data, new line is
     * appended (that is a solaris sed behavior). libsed's internal memory for
     * evaluation is allocated on request's pool so it will be cleared once
     * request is over.
     *
     * If flush bucket is found then append the flush bucket to ctx->bb
     * and pass it to next filter. There may be some data which will still be
     * in sed's internal buffer which can't be flushed until new line
     * character is arrived.
     */
    for (b = APR_BRIGADE_FIRST(bb); b != APR_BRIGADE_SENTINEL(bb);) {
        const char *buf = NULL;
        apr_size_t bytes = 0;
        if (APR_BUCKET_IS_EOS(b)) {
            apr_bucket *b1 = APR_BUCKET_NEXT(b);
            /* Now clean up the internal sed buffer */
            sed_finalize_eval(&ctx->eval, ctx);
            status = flush_output_buffer(ctx);
            if (status != APR_SUCCESS) {
                clear_ctxpool(ctx);
                return status;
            }
            APR_BUCKET_REMOVE(b);
            /* Insert the eos bucket to ctx->bb brigade */
            APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
            b = b1;
        }
        else if (APR_BUCKET_IS_FLUSH(b)) {
            apr_bucket *b1 = APR_BUCKET_NEXT(b);
            APR_BUCKET_REMOVE(b);
            status = flush_output_buffer(ctx);
            if (status != APR_SUCCESS) {
                clear_ctxpool(ctx);
                return status;
            }
            APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
            b = b1;
        }
        else if (APR_BUCKET_IS_METADATA(b)) {
            b = APR_BUCKET_NEXT(b);
        }
        else if (apr_bucket_read(b, &buf, &bytes, APR_BLOCK_READ)
                 == APR_SUCCESS) {
            apr_bucket *b1 = APR_BUCKET_NEXT(b);
            status = sed_eval_buffer(&ctx->eval, buf, bytes, ctx);
            if (status != APR_SUCCESS) {
                clear_ctxpool(ctx);
                return status;
            }
            APR_BUCKET_REMOVE(b);
            apr_bucket_delete(b);
            b = b1;
        }
        else {
            apr_bucket *b1 = APR_BUCKET_NEXT(b);
            APR_BUCKET_REMOVE(b);
            b = b1;
        }
    }
    apr_brigade_cleanup(bb);
    status = flush_output_buffer(ctx);
    if (status != APR_SUCCESS) {
        clear_ctxpool(ctx);
        return status;
    }
    if (!APR_BRIGADE_EMPTY(ctx->bb)) {
        status = ap_pass_brigade(f->next, ctx->bb);
        apr_brigade_cleanup(ctx->bb);
    }
    clear_ctxpool(ctx);
    return status;
}