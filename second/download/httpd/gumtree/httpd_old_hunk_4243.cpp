    
    if (APLOGcdebug(session->c)) {
        char buffer[256];
        
        h2_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03063)
                      "h2_session(%ld): recv unknown FRAME[%s], frames=%ld/%ld (r/s)",
                      session->id, buffer, (long)session->frames_received,
                     (long)session->frames_sent);
    }
    return 0;
}

static int on_data_chunk_recv_cb(nghttp2_session *ngh2, uint8_t flags,
                                 int32_t stream_id,
                                 const uint8_t *data, size_t len, void *userp)
{
    h2_session *session = (h2_session *)userp;
    apr_status_t status = APR_SUCCESS;
