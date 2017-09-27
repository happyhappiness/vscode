                                       apr_size_t *readlen);

static int is_accepting_streams(h2_session *session); 
static void dispatch_event(h2_session *session, h2_session_event_t ev, 
                             int err, const char *msg);

apr_status_t h2_session_stream_done(h2_session *session, h2_stream *stream)
{
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_stream(%ld-%d): EOS bucket cleanup -> done", 
                  session->id, stream->id);
    h2_ihash_remove(session->streams, stream->id);
    h2_mplx_stream_done(session->mplx, stream);
    
    dispatch_event(session, H2_SESSION_EV_STREAM_DONE, 0, NULL);
    return APR_SUCCESS;
}

typedef struct stream_sel_ctx {
    h2_session *session;
    h2_stream *candidate;
} stream_sel_ctx;

static int find_cleanup_stream(void *udata, void *sdata)
