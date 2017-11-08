static int win_update_iter(void *udata, void *val)
{
    win_update_ctx *ctx = udata;
    h2_proxy_stream *stream = val;
    
    if (stream->r && stream->r->connection == ctx->c) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, ctx->session->c, 
                      "h2_proxy_session(%s-%d): win_update %ld bytes",
                      ctx->session->id, (int)stream->id, (long)ctx->bytes);
        nghttp2_session_consume(ctx->session->ngh2, stream->id, ctx->bytes);
        ctx->updated = 1;
        return 0;
    }
    return 1;
}