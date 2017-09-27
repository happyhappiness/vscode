                          APLOGNO(02938) "h2_stream(%ld-%d): reading data",
                          session->id, (int)stream_id);
            return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    if (eos) {
        *data_flags |= NGHTTP2_DATA_FLAG_EOF;
    }
    
    return (ssize_t)nread;
}

typedef struct {
    nghttp2_nv *nv;
    size_t nvlen;
    size_t offset;
} nvctx_t;

static int submit_response(h2_session *session, h2_response *response)
{
    nghttp2_data_provider provider;
    int rv;
    
    memset(&provider, 0, sizeof(provider));
    provider.source.fd = response->stream_id;
    provider.read_callback = stream_data_cb;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                  "h2_stream(%ld-%d): submitting response %s",
                  session->id, response->stream_id, response->status);
    
    rv = nghttp2_submit_response(session->ngh2, response->stream_id,
                                 response->ngheader->nv, 
                                 response->ngheader->nvlen, &provider);
    
    if (rv != 0) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                      APLOGNO(02939) "h2_stream(%ld-%d): submit_response: %s",
                      session->id, response->stream_id, nghttp2_strerror(rv));
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): submitted response %s, rv=%d",
                      session->id, response->stream_id, 
                      response->status, rv);
    }
    return rv;
}

/* Start submitting the response to a stream request. This is possible
 * once we have all the response headers. The response body will be
 * read by the session using the callback we supply.
 */
apr_status_t h2_session_handle_response(h2_session *session, h2_stream *stream)
{
    apr_status_t status = APR_SUCCESS;
    int rv = 0;
    AP_DEBUG_ASSERT(session);
    AP_DEBUG_ASSERT(stream);
    AP_DEBUG_ASSERT(stream->response);
    
    if (stream->response->ngheader) {
        rv = submit_response(session, stream->response);
    }
    else {
        rv = nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE,
                                       stream->id, NGHTTP2_PROTOCOL_ERROR);
    }
    
    if (nghttp2_is_fatal(rv)) {
        status = APR_EGENERAL;
        h2_session_abort_int(session, rv);
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                      APLOGNO(02940) "submit_response: %s", 
                      nghttp2_strerror(rv));
    }
    return status;
}

int h2_session_is_done(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    return (session->aborted
            || !session->ngh2
            || (!nghttp2_session_want_read(session->ngh2)
                && !nghttp2_session_want_write(session->ngh2)));
}

static int log_stream(void *ctx, h2_stream *stream)
{
    h2_session *session = (h2_session *)ctx;
    AP_DEBUG_ASSERT(session);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                  "h2_stream(%ld-%d): in set, suspended=%d, aborted=%d, "
                  "has_data=%d",
                  session->id, stream->id, stream->suspended, stream->aborted,
                  h2_mplx_out_has_data_for(session->mplx, stream->id));
    return 1;
}

void h2_session_log_stats(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                  "h2_session(%ld): %d open streams",
                  session->id, (int)h2_stream_set_size(session->streams));
    h2_stream_set_iter(session->streams, log_stream, session);
}

static int frame_print(const nghttp2_frame *frame, char *buffer, size_t maxlen)
{
    char scratch[128];
    size_t s_len = sizeof(scratch)/sizeof(scratch[0]);
