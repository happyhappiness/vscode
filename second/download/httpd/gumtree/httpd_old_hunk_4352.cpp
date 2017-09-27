    rv = apr_brigade_vprintf(bb, NULL, NULL, fmt, args);
    va_end(args);

    return rv;
}

static apr_status_t h2_status_stream_filter(h2_stream *stream)
{
    h2_session *session = stream->session;
    h2_mplx *mplx = session->mplx;
    conn_rec *c = session->c;
    h2_push_diary *diary;
    apr_bucket_brigade *bb;
    apr_status_t status;
    
    if (!stream->response) {
        return APR_EINVAL;
    }
    
    if (!stream->buffer) {
        stream->buffer = apr_brigade_create(stream->pool, c->bucket_alloc);
    }
    bb = stream->buffer;
    
    apr_table_unset(stream->response->headers, "Content-Length");
    stream->response->content_length = -1;
    
    bbout(bb, "{\n");
    bbout(bb, "  \"HTTP2\": \"on\",\n");
    bbout(bb, "  \"H2PUSH\": \"%s\",\n", h2_session_push_enabled(session)? "on" : "off");
    bbout(bb, "  \"mod_http2_version\": \"%s\",\n", MOD_HTTP2_VERSION);
    bbout(bb, "  \"session_id\": %ld,\n", (long)session->id);
    bbout(bb, "  \"streams_max\": %d,\n", (int)session->max_stream_count);
    bbout(bb, "  \"this_stream\": %d,\n", stream->id);
    bbout(bb, "  \"streams_open\": %d,\n", (int)h2_ihash_count(session->streams));
    bbout(bb, "  \"max_stream_started\": %d,\n", mplx->max_stream_started);
    bbout(bb, "  \"requests_received\": %d,\n", session->remote.emitted_count);
    bbout(bb, "  \"responses_submitted\": %d,\n", session->responses_submitted);
    bbout(bb, "  \"streams_reset\": %d, \n", session->streams_reset);
    bbout(bb, "  \"pushes_promised\": %d,\n", session->pushes_promised);
    bbout(bb, "  \"pushes_submitted\": %d,\n", session->pushes_submitted);
    bbout(bb, "  \"pushes_reset\": %d,\n", session->pushes_reset);
    
    diary = session->push_diary;
    if (diary) {
        const char *data;
        const char *base64_digest;
        apr_size_t len;
        
        status = h2_push_diary_digest_get(diary, stream->pool, 256, 
                                          stream->request->authority, &data, &len);
        if (status == APR_SUCCESS) {
            base64_digest = h2_util_base64url_encode(data, len, stream->pool);
            bbout(bb, "  \"cache_digest\": \"%s\",\n", base64_digest);
        }
        
        /* try the reverse for testing purposes */
        status = h2_push_diary_digest_set(diary, stream->request->authority, data, len);
        if (status == APR_SUCCESS) {
            status = h2_push_diary_digest_get(diary, stream->pool, 256, 
                                              stream->request->authority, &data, &len);
            if (status == APR_SUCCESS) {
                base64_digest = h2_util_base64url_encode(data, len, stream->pool);
                bbout(bb, "  \"cache_digest^2\": \"%s\",\n", base64_digest);
            }
        }
    }
    bbout(bb, "  \"frames_received\": %ld,\n", (long)session->frames_received);
    bbout(bb, "  \"frames_sent\": %ld,\n", (long)session->frames_sent);
    bbout(bb, "  \"bytes_received\": %"APR_UINT64_T_FMT",\n", session->io.bytes_read);
    bbout(bb, "  \"bytes_sent\": %"APR_UINT64_T_FMT"\n", session->io.bytes_written);
    bbout(bb, "}\n");
    
    return APR_SUCCESS;
}

apr_status_t h2_stream_filter(h2_stream *stream)
{
    const char *fname = stream->response? stream->response->sos_filter : NULL; 
    if (fname && !strcmp(H2_SOS_H2_STATUS, fname)) {
        return h2_status_stream_filter(stream);
    }
    return APR_SUCCESS;
}

