
typedef struct {
    h2_proxy_session *session;
    h2_proxy_request_done *done;
} cleanup_iter_ctx;

static int done_iter(void *udata, void *val)
{
    cleanup_iter_ctx *ctx = udata;
    h2_proxy_stream *stream = val;
    int touched = (!ctx->session->last_stream_id || 
                   stream->id <= ctx->session->last_stream_id);
    ctx->done(ctx->session, stream->r, 0, touched);
    return 1;
}

void h2_proxy_session_cleanup(h2_proxy_session *session, 
                              h2_proxy_request_done *done)
{
    if (session->streams && !h2_ihash_empty(session->streams)) {
        cleanup_iter_ctx ctx;
        ctx.session = session;
        ctx.done = done;
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03366)
                      "h2_proxy_session(%s): terminated, %d streams unfinished",
                      session->id, (int)h2_ihash_count(session->streams));
        h2_ihash_iter(session->streams, done_iter, &ctx);
        h2_ihash_clear(session->streams);
    }
}

typedef struct {
    h2_proxy_session *session;
    conn_rec *c;
