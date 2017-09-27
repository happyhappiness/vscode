            *readlen = n;
        }
    }
    return APR_SUCCESS;
}

apr_status_t h2_session_close(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    if (!session->aborted) {
        h2_session_abort_int(session, 0);
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0,session->c,
                  "h2_session: closing, writing eoc");
    
    h2_session_cleanup(session);
    return h2_conn_io_close(&session->io, session);           
}

static ssize_t stream_data_cb(nghttp2_session *ng2s,
                              int32_t stream_id,
                              uint8_t *buf,
                              size_t length,
                              uint32_t *data_flags,
                              nghttp2_data_source *source,
                              void *puser)
{
    h2_session *session = (h2_session *)puser;
    apr_off_t nread = length;
    int eos = 0;
    apr_status_t status;
    h2_stream *stream;
    AP_DEBUG_ASSERT(session);
    
    /* The session wants to send more DATA for the stream. We need
     * to find out how much of the requested length we can send without
     * blocking.
     * Indicate EOS when we encounter it or DEFERRED if the stream
     * should be suspended.
     * TODO: for handling of TRAILERS,  the EOF indication needs
     * to be aware of that.
     */
 
    (void)ng2s;
    (void)buf;
    (void)source;
    stream = h2_session_get_stream(session, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                      APLOGNO(02937) 
                      "h2_stream(%ld-%d): data requested but stream not found",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
