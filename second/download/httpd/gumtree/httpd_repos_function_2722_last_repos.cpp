static int done_iter(void *udata, void *val)
{
    cleanup_iter_ctx *ctx = udata;
    h2_proxy_stream *stream = val;
    int touched = (stream->data_sent || 
                   stream->id <= ctx->session->last_stream_id);
    ctx->done(ctx->session, stream->r, APR_ECONNABORTED, touched);
    return 1;
}