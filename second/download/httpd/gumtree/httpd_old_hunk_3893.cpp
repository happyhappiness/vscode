        }
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): closing with err=%d %s", 
                      session->id, (int)stream->id, (int)error_code,
                      nghttp2_strerror(error_code));
    }
    
    h2_stream_set_remove(session->streams, stream);
    return h2_mplx_cleanup_stream(session->mplx, stream);
}

static int on_stream_close_cb(nghttp2_session *ngh2, int32_t stream_id,
                              uint32_t error_code, void *userp)
{
    h2_session *session = (h2_session *)userp;
    h2_stream *stream;
    
    (void)ngh2;
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    stream = h2_stream_set_get(session->streams, stream_id);
    if (stream) {
        stream_destroy(session, stream, error_code);
    }
    
    if (error_code) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): close error %d",
                      session->id, (int)stream_id, error_code);
    }
    
    return 0;
}

static int on_begin_headers_cb(nghttp2_session *ngh2,
                               const nghttp2_frame *frame, void *userp)
{
    /* This starts a new stream. */
    int rv;
    (void)ngh2;
    rv = stream_open((h2_session *)userp, frame->hd.stream_id);
    if (rv != NGHTTP2_ERR_CALLBACK_FAILURE) {
      /* on_header_cb or on_frame_recv_cb will dectect that stream
         does not exist and submit RST_STREAM. */
      return 0;
    }
    return NGHTTP2_ERR_CALLBACK_FAILURE;
}

static int on_header_cb(nghttp2_session *ngh2, const nghttp2_frame *frame,
                        const uint8_t *name, size_t namelen,
                        const uint8_t *value, size_t valuelen,
                        uint8_t flags,
