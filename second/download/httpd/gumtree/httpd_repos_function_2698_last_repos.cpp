static void stream_resume(h2_proxy_stream *stream)
{
    h2_proxy_session *session = stream->session;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  "h2_proxy_stream(%s-%d): resuming", 
                  session->id, stream->id);
    stream->suspended = 0;
    h2_proxy_iq_remove(session->suspended, stream->id);
    nghttp2_session_resume_data(session->ngh2, stream->id);
    dispatch_event(session, H2_PROXYS_EV_STREAM_RESUMED, 0, NULL);
}