static apr_status_t sed_write_output(void *dummy, char *buf, int sz)
{
    /* dummy is basically filter context. Context is passed during invocation
     * of sed_eval_buffer
     */
    int remainbytes = 0;
    apr_status_t status = APR_SUCCESS;
    sed_filter_ctxt *ctx = (sed_filter_ctxt *) dummy;
    if (ctx->outbuf == NULL) {
        alloc_outbuf(ctx);
    }
    remainbytes = ctx->bufsize - (ctx->curoutbuf - ctx->outbuf);
    if (sz >= remainbytes) {
        if (remainbytes > 0) {
            memcpy(ctx->curoutbuf, buf, remainbytes);
            buf += remainbytes;
            sz -= remainbytes;
            ctx->curoutbuf += remainbytes;
        }
        /* buffer is now full */
        status = append_bucket(ctx, ctx->outbuf, ctx->bufsize);
        /* old buffer is now used so allocate new buffer */
        alloc_outbuf(ctx);
        /* if size is bigger than the allocated buffer directly add to output
         * brigade */
        if ((status == APR_SUCCESS) && (sz >= ctx->bufsize)) {
            char* newbuf = apr_pmemdup(ctx->tpool, buf, sz);
            status = append_bucket(ctx, newbuf, sz);
            /* pool might get clear after append_bucket */
            if (ctx->outbuf == NULL) {
                alloc_outbuf(ctx);
            }
        }
        else {
            memcpy(ctx->curoutbuf, buf, sz);
            ctx->curoutbuf += sz;
        }
    }
    else {
        memcpy(ctx->curoutbuf, buf, sz);
        ctx->curoutbuf += sz;
    }
    return status;
}