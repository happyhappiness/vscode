    else if (APR_STATUS_IS_EOF(rv)) {
        return NGHTTP2_ERR_EOF;
    }
    return NGHTTP2_ERR_PROTO;
}

static void update_window(void *ctx, int stream_id, apr_off_t bytes_read)
{
    h2_session *session = (h2_session*)ctx;
    nghttp2_session_consume(session->ngh2, stream_id, bytes_read);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_session(%ld-%d): consumed %ld bytes",
                  session->id, stream_id, (long)bytes_read);
}

static apr_status_t h2_session_receive(void *ctx, 
                                       const char *data, apr_size_t len,
                                       apr_size_t *readlen);

static void dispatch_event(h2_session *session, h2_session_event_t ev, 
                             int err, const char *msg);

apr_status_t h2_session_stream_done(h2_session *session, h2_stream *stream)
{
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_stream(%ld-%d): EOS bucket cleanup -> done", 
                  session->id, stream->id);
    h2_mplx_stream_done(session->mplx, stream);
    
    dispatch_event(session, H2_SESSION_EV_STREAM_DONE, 0, NULL);
    return APR_SUCCESS;
}

typedef struct stream_sel_ctx {
    h2_session *session;
    h2_stream *candidate;
} stream_sel_ctx;

static int find_cleanup_stream(h2_stream *stream, void *ictx)
{
    stream_sel_ctx *ctx = ictx;
    if (H2_STREAM_CLIENT_INITIATED(stream->id)) {
        if (!ctx->session->local.accepting
            && stream->id > ctx->session->local.accepted_max) {
            ctx->candidate = stream;
            return 0;
        }
    }
    else {
        if (!ctx->session->remote.accepting
            && stream->id > ctx->session->remote.accepted_max) {
            ctx->candidate = stream;
            return 0;
        }
    }
    return 1;
}

static void cleanup_streams(h2_session *session)
{
    stream_sel_ctx ctx;
    ctx.session = session;
    ctx.candidate = NULL;
    while (1) {
        h2_mplx_stream_do(session->mplx, find_cleanup_stream, &ctx);
        if (ctx.candidate) {
            h2_session_stream_done(session, ctx.candidate);
            ctx.candidate = NULL;
        }
        else {
            break;
        }
    }
}

h2_stream *h2_session_open_stream(h2_session *session, int stream_id,
                                  int initiated_on, const h2_request *req)
{
    h2_stream * stream;
    apr_pool_t *stream_pool;
    
    apr_pool_create(&stream_pool, session->pool);
    apr_pool_tag(stream_pool, "h2_stream");
    
    stream = h2_stream_open(stream_id, stream_pool, session, 
                            initiated_on);
    nghttp2_session_set_stream_user_data(session->ngh2, stream_id, stream);
    
    if (req) {
        h2_stream_set_request(stream, req);
    }
    
    if (H2_STREAM_CLIENT_INITIATED(stream_id)) {
        if (stream_id > session->remote.emitted_max) {
            ++session->remote.emitted_count;
            session->remote.emitted_max = stream->id;
            session->local.accepted_max = stream->id;
        }
    }
    else {
        if (stream_id > session->local.emitted_max) {
            ++session->local.emitted_count;
            session->remote.emitted_max = stream->id;
        }
    }
    dispatch_event(session, H2_SESSION_EV_STREAM_OPEN, 0, NULL);
    
    return stream;
}

/**
 * Determine the importance of streams when scheduling tasks.
 * - if both stream depend on the same one, compare weights
