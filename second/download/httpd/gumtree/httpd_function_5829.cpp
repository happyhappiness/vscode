static int on_frame_send_cb(nghttp2_session *ngh2,
                            const nghttp2_frame *frame,
                            void *userp)
{
    h2_session *session = (h2_session *)userp;
    (void)ngh2; (void)frame;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_session(%ld): on_frame_send", session->id);
    return 0;
}