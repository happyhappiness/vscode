 * we need to handle ourself.
 */
static int on_frame_recv_cb(nghttp2_session *ng2s,
                            const nghttp2_frame *frame,
                            void *userp)
{
    h2_session *session = (h2_session *)userp;
    apr_status_t status = APR_SUCCESS;
    h2_stream *stream;
    
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_stream(%ld-%d): on_frame_rcv #%ld, type=%d", 
                  session->id, frame->hd.stream_id, 
                  (long)session->frames_received, frame->hd.type);

    ++session->frames_received;
    switch (frame->hd.type) {
        case NGHTTP2_HEADERS:
            /* This can be HEADERS for a new stream, defining the request,
             * or HEADER may come after DATA at the end of a stream as in
             * trailers */
            stream = h2_session_get_stream(session, frame->hd.stream_id);
            if (stream) {
                int eos = (frame->hd.flags & NGHTTP2_FLAG_END_STREAM);
                
                if (h2_stream_is_scheduled(stream)) {
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                                  "h2_stream(%ld-%d): TRAILER, eos=%d", 
                                  session->id, frame->hd.stream_id, eos);
                    if (eos) {
                        status = h2_stream_close_input(stream);
                    }
                }
                else {
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                                  "h2_stream(%ld-%d): HEADER, eos=%d", 
                                  session->id, frame->hd.stream_id, eos);
                    status = stream_schedule(session, stream, eos);
                }
            }
            else {
                status = APR_EINVAL;
            }
            break;
        case NGHTTP2_DATA:
            stream = h2_session_get_stream(session, frame->hd.stream_id);
            if (stream) {
                int eos = (frame->hd.flags & NGHTTP2_FLAG_END_STREAM);
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                              "h2_stream(%ld-%d): DATA, len=%ld, eos=%d", 
                              session->id, frame->hd.stream_id, 
                              (long)frame->hd.length, eos);
                if (eos) {
                    status = h2_stream_close_input(stream);
                }
            }
            else {
                status = APR_EINVAL;
            }
            break;
        case NGHTTP2_PRIORITY:
            session->reprioritize = 1;
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_session:  stream(%ld-%d): PRIORITY frame "
                          " weight=%d, dependsOn=%d, exclusive=%d", 
                          session->id, (int)frame->hd.stream_id,
                          frame->priority.pri_spec.weight,
                          frame->priority.pri_spec.stream_id,
                          frame->priority.pri_spec.exclusive);
            break;
        case NGHTTP2_WINDOW_UPDATE:
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_session:  stream(%ld-%d): WINDOW_UPDATE "
                          "incr=%d", 
                          session->id, (int)frame->hd.stream_id,
                          frame->window_update.window_size_increment);
            break;
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

    if (status != APR_SUCCESS) {
        int rv;
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                      APLOGNO(02923) 
                      "h2_session: stream(%ld-%d): error handling frame",
                      session->id, (int)frame->hd.stream_id);
        rv = nghttp2_submit_rst_stream(ng2s, NGHTTP2_FLAG_NONE,
                                       frame->hd.stream_id,
                                       NGHTTP2_INTERNAL_ERROR);
        if (nghttp2_is_fatal(rv)) {
            return NGHTTP2_ERR_CALLBACK_FAILURE;
        }
    }
    
    return 0;
}

static apr_status_t pass_data(void *ctx, 
                              const char *data, apr_off_t length)
{
    return h2_conn_io_write(&((h2_session*)ctx)->io, data, length);
}


static char immortal_zeros[H2_MAX_PADLEN];

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
    unsigned char padlen;
    int eos;
    h2_stream *stream;
    
    (void)ngh2;
    (void)source;
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    if (frame->data.padlen > H2_MAX_PADLEN) {
        return NGHTTP2_ERR_PROTO;
    }
    padlen = (unsigned char)frame->data.padlen;
    
    stream = h2_session_get_stream(session, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_NOTFOUND, session->c,
                      APLOGNO(02924) 
                      "h2_stream(%ld-%d): send_data",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_stream(%ld-%d): send_data_cb for %ld bytes",
                  session->id, (int)stream_id, (long)length);
                  
    if (h2_conn_io_is_buffered(&session->io)) {
        status = h2_conn_io_write(&session->io, (const char *)framehd, 9);
        if (status == APR_SUCCESS) {
            if (padlen) {
                status = h2_conn_io_write(&session->io, (const char *)&padlen, 1);
            }
            
            if (status == APR_SUCCESS) {
                apr_off_t len = length;
                status = h2_stream_readx(stream, pass_data, session, &len, &eos);
                if (status == APR_SUCCESS && len != length) {
                    status = APR_EINVAL;
                }
            }
            
            if (status == APR_SUCCESS && padlen) {
                if (padlen) {
                    status = h2_conn_io_write(&session->io, immortal_zeros, padlen);
                }
            }
        }
    }
    else {
        apr_bucket *b;
        char *header = apr_pcalloc(stream->pool, 10);
        memcpy(header, (const char *)framehd, 9);
        if (padlen) {
            header[9] = (char)padlen;
        }
        b = apr_bucket_pool_create(header, padlen? 10 : 9, 
                                   stream->pool, session->c->bucket_alloc);
        status = h2_conn_io_writeb(&session->io, b);
        
        if (status == APR_SUCCESS) {
            apr_off_t len = length;
            status = h2_stream_read_to(stream, session->io.output, &len, &eos);
            if (status == APR_SUCCESS && len != length) {
                status = APR_EINVAL;
            }
        }
            
        if (status == APR_SUCCESS && padlen) {
            b = apr_bucket_immortal_create(immortal_zeros, padlen, 
                                           session->c->bucket_alloc);
            status = h2_conn_io_writeb(&session->io, b);
        }
    }
    
    
    if (status == APR_SUCCESS) {
        stream->data_frames_sent++;
        h2_conn_io_consider_flush(&session->io);
        return 0;
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                      APLOGNO(02925) 
                      "h2_stream(%ld-%d): failed send_data_cb",
                      session->id, (int)stream_id);
    }
    
    return h2_session_status_from_apr_status(status);
}

static int on_frame_send_cb(nghttp2_session *ngh2, 
                            const nghttp2_frame *frame,
                            void *user_data)
{
    h2_session *session = user_data;
    if (APLOGcdebug(session->c)) {
        char buffer[256];
        
        frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_session(%ld): frame_send %s",
                      session->id, buffer);
    }
    return 0;
}

#define NGH2_SET_CALLBACK(callbacks, name, fn)\
nghttp2_session_callbacks_set_##name##_callback(callbacks, fn)

static apr_status_t init_callbacks(conn_rec *c, nghttp2_session_callbacks **pcb)
{
