 * we need to handle ourself.
 */
static int on_frame_recv_cb(nghttp2_session *ng2s,
                            const nghttp2_frame *frame,
                            void *userp)
{
    int rv;
    h2_session *session = (h2_session *)userp;
    apr_status_t status = APR_SUCCESS;
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    ++session->frames_received;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                  "h2_session(%ld): on_frame_rcv #%ld, type=%d", session->id,
                  (long)session->frames_received, frame->hd.type);
    switch (frame->hd.type) {
        case NGHTTP2_HEADERS: {
            int eos;
            h2_stream * stream = h2_stream_set_get(session->streams,
                                                   frame->hd.stream_id);
            if (stream == NULL) {
                ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                              APLOGNO(02921) 
                              "h2_session:  stream(%ld-%d): HEADERS frame "
                              "for unknown stream", session->id,
                              (int)frame->hd.stream_id);
                rv = nghttp2_submit_rst_stream(ng2s, NGHTTP2_FLAG_NONE,
                                               frame->hd.stream_id,
                                               NGHTTP2_INTERNAL_ERROR);
                if (nghttp2_is_fatal(rv)) {
                    return NGHTTP2_ERR_CALLBACK_FAILURE;
                }
                return 0;
            }

            eos = (frame->hd.flags & NGHTTP2_FLAG_END_STREAM);
            status = stream_end_headers(session, stream, eos);

            break;
        }
        case NGHTTP2_DATA: {
            h2_stream * stream = h2_stream_set_get(session->streams,
                                                   frame->hd.stream_id);
            if (stream == NULL) {
                ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                              APLOGNO(02922) 
                              "h2_session:  stream(%ld-%d): DATA frame "
                              "for unknown stream", session->id,
                              (int)frame->hd.stream_id);
                rv = nghttp2_submit_rst_stream(ng2s, NGHTTP2_FLAG_NONE,
                                               frame->hd.stream_id,
                                               NGHTTP2_INTERNAL_ERROR);
                if (nghttp2_is_fatal(rv)) {
                    return NGHTTP2_ERR_CALLBACK_FAILURE;
                }
                return 0;
            }
            break;
        }
        case NGHTTP2_PRIORITY: {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          "h2_session:  stream(%ld-%d): PRIORITY frame "
                          " weight=%d, dependsOn=%d, exclusive=%d", 
                          session->id, (int)frame->hd.stream_id,
                          frame->priority.pri_spec.weight,
                          frame->priority.pri_spec.stream_id,
                          frame->priority.pri_spec.exclusive);
            break;
        }
        default:
            if (APLOGctrace2(session->c)) {
                char buffer[256];
                
                frame_print(frame, buffer,
                            sizeof(buffer)/sizeof(buffer[0]));
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                              "h2_session: on_frame_rcv %s", buffer);
            }
            break;
    }

    /* only DATA and HEADERS frame can bear END_STREAM flag.  Other
       frame types may have other flag which has the same value, so we
       have to check the frame type first.  */
    if ((frame->hd.type == NGHTTP2_DATA || frame->hd.type == NGHTTP2_HEADERS) &&
        frame->hd.flags & NGHTTP2_FLAG_END_STREAM) {
        h2_stream * stream = h2_stream_set_get(session->streams,
                                               frame->hd.stream_id);
        if (stream != NULL) {
            status = h2_stream_write_eos(stream);
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                          "h2_stream(%ld-%d): input closed",
                          session->id, (int)frame->hd.stream_id);
        }
    }
    
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                      APLOGNO(02923) 
                      "h2_session: stream(%ld-%d): error handling frame",
                      session->id, (int)frame->hd.stream_id);
        rv = nghttp2_submit_rst_stream(ng2s, NGHTTP2_FLAG_NONE,
                                       frame->hd.stream_id,
                                       NGHTTP2_INTERNAL_ERROR);
        if (nghttp2_is_fatal(rv)) {
            return NGHTTP2_ERR_CALLBACK_FAILURE;
        }
        return 0;
    }
    
    return 0;
}

static apr_status_t send_data(h2_session *session, const char *data, 
                              apr_size_t length)
{
    return h2_conn_io_write(&session->io, data, length);
}

static apr_status_t pass_data(void *ctx, 
                              const char *data, apr_size_t length)
{
    return send_data((h2_session*)ctx, data, length);
}

static int on_send_data_cb(nghttp2_session *ngh2, 
                           nghttp2_frame *frame, 
                           const uint8_t *framehd, 
                           size_t length, 
                           nghttp2_data_source *source, 
                           void *userp)
{
    apr_status_t status = APR_SUCCESS;
    h2_session *session = (h2_session *)userp;
    int stream_id = (int)frame->hd.stream_id;
    const unsigned char padlen = frame->data.padlen;
    int eos;
    h2_stream *stream;
    
    (void)ngh2;
    (void)source;
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    stream = h2_stream_set_get(session->streams, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_NOTFOUND, session->c,
                      APLOGNO(02924) 
                      "h2_stream(%ld-%d): send_data",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    status = send_data(session, (const char *)framehd, 9);
    if (status == APR_SUCCESS) {
        if (padlen) {
            status = send_data(session, (const char *)&padlen, 1);
        }

        if (status == APR_SUCCESS) {
            apr_size_t len = length;
            status = h2_stream_readx(stream, pass_data, session, 
                                     &len, &eos);
            if (status == APR_SUCCESS && len != length) {
                status = APR_EINVAL;
            }
        }
        
        if (status == APR_SUCCESS && padlen) {
            if (padlen) {
                char pad[256];
                memset(pad, 0, padlen);
                status = send_data(session, pad, padlen);
            }
        }
    }
    
    if (status == APR_SUCCESS) {
        return 0;
    }
    else if (status != APR_EOF) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                      APLOGNO(02925) 
                      "h2_stream(%ld-%d): failed send_data_cb",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    return h2_session_status_from_apr_status(status);
}


#define NGH2_SET_CALLBACK(callbacks, name, fn)\
nghttp2_session_callbacks_set_##name##_callback(callbacks, fn)

static apr_status_t init_callbacks(conn_rec *c, nghttp2_session_callbacks **pcb)
{
