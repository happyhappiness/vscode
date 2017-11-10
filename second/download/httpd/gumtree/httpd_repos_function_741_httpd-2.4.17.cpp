static int bio_filter_out_pass(bio_filter_out_ctx_t *outctx)
{
    AP_DEBUG_ASSERT(!APR_BRIGADE_EMPTY(outctx->bb));

    outctx->rc = ap_pass_brigade(outctx->filter_ctx->pOutputFilter->next,
                                 outctx->bb);
    /* Fail if the connection was reset: */
    if (outctx->rc == APR_SUCCESS && outctx->c->aborted) {
        outctx->rc = APR_ECONNRESET;
    }
    return (outctx->rc == APR_SUCCESS) ? 1 : -1;
}