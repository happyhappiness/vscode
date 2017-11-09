static int cancel_iter(void *udata, void *val)
{
    cleanup_iter_ctx *ctx = udata;
    h2_proxy_stream *stream = val;
    nghttp2_submit_rst_stream(ctx->session->ngh2, NGHTTP2_FLAG_NONE,
                              stream->id, 0);
    return 1;
}