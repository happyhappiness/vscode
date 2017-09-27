
static void h2_session_ev_pre_close(h2_session *session, int arg, const char *msg)
{
    h2_session_shutdown(session, arg, msg, 1);
}

static void ev_stream_open(h2_session *session, h2_stream *stream)
{
    h2_iq_append(session->in_process, stream->id);
    switch (session->state) {
        case H2_SESSION_ST_IDLE:
            if (session->open_streams == 1) {
                /* enter timeout, since we have a stream again */
                session->idle_until = (session->s->timeout + apr_time_now());
            }
            break;
        default:
            break;
    }
}

static void ev_stream_closed(h2_session *session, h2_stream *stream)
{
    apr_bucket *b;
    
    if (H2_STREAM_CLIENT_INITIATED(stream->id)
        && (stream->id > session->local.completed_max)) {
        session->local.completed_max = stream->id;
    }
    switch (session->state) {
        case H2_SESSION_ST_IDLE:
            if (session->open_streams == 0) {
                /* enter keepalive timeout, since we no longer have streams */
                session->idle_until = (session->s->keep_alive_timeout
                                       + apr_time_now());
            }
            break;
        default:
            break;
    }
    
    /* The stream might have data in the buffers of the main connection.
     * We can only free the allocated resources once all had been written.
     * Send a special buckets on the connection that gets destroyed when
     * all preceding data has been handled. On its destruction, it is safe
     * to purge all resources of the stream. */
    b = h2_bucket_eos_create(session->c->bucket_alloc, stream);
    APR_BRIGADE_INSERT_TAIL(session->bbtmp, b);
    h2_conn_io_pass(&session->io, session->bbtmp);
    apr_brigade_cleanup(session->bbtmp);
}

static void on_stream_state_enter(void *ctx, h2_stream *stream)
{
    h2_session *session = ctx;
    /* stream entered a new state */
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  H2_STRM_MSG(stream, "entered state"));
    switch (stream->state) {
        case H2_SS_IDLE: /* stream was created */
            ++session->open_streams;
            if (H2_STREAM_CLIENT_INITIATED(stream->id)) {
                ++session->remote.emitted_count;
                if (stream->id > session->remote.emitted_max) {
                    session->remote.emitted_max = stream->id;
                    session->local.accepted_max = stream->id;
                }
            }
            else {
                if (stream->id > session->local.emitted_max) {
                    ++session->local.emitted_count;
                    session->remote.emitted_max = stream->id;
                }
            }
            break;
        case H2_SS_OPEN: /* stream has request headers */
        case H2_SS_RSVD_L: /* stream has request headers */
            ev_stream_open(session, stream);
            break;
        case H2_SS_CLOSED_L: /* stream output was closed */
            break;
        case H2_SS_CLOSED_R: /* stream input was closed */
            break;
        case H2_SS_CLOSED: /* stream in+out were closed */
            --session->open_streams;
            ev_stream_closed(session, stream);
            break;
        case H2_SS_CLEANUP:
            h2_mplx_stream_cleanup(session->mplx, stream);
            break;
        default:
            break;
    }
}

static void on_stream_event(void *ctx, h2_stream *stream, 
                                  h2_stream_event_t ev)
{
    h2_session *session = ctx;
    switch (ev) {
        case H2_SEV_IN_DATA_PENDING:
            h2_iq_append(session->in_pending, stream->id);
            break;
        default:
            /* NOP */
            break;
    }
}

static void on_stream_state_event(void *ctx, h2_stream *stream, 
                                  h2_stream_event_t ev)
{
    h2_session *session = ctx;
    switch (ev) {
        case H2_SEV_CANCELLED:
            if (session->state != H2_SESSION_ST_DONE) {
                nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE, 
                                          stream->id, stream->rst_error);
            }
            break;
        default:
            /* NOP */
            break;
    }
}

static void dispatch_event(h2_session *session, h2_session_event_t ev, 
                      int arg, const char *msg)
{
    switch (ev) {
