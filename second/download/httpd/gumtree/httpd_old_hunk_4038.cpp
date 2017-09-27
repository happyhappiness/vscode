            status = APR_EGENERAL;
            ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                          APLOGNO(02970) "nghttp2_submit_window_update: %s", 
                          nghttp2_strerror(*rv));        
        }
    }
    return status;
}

typedef struct {
    h2_session *session;
    int resume_count;
} resume_ctx;

static int resume_on_data(void *ctx, h2_stream *stream) {
    resume_ctx *rctx = (resume_ctx*)ctx;
    h2_session *session = rctx->session;
    AP_DEBUG_ASSERT(session);
    AP_DEBUG_ASSERT(stream);
    
    if (h2_stream_is_suspended(stream)) {
        if (h2_mplx_out_has_data_for(stream->session->mplx, stream->id)) {
            int rv;
            h2_stream_set_suspended(stream, 0);
            ++rctx->resume_count;
            
            rv = nghttp2_session_resume_data(session->ngh2, stream->id);
            ap_log_cerror(APLOG_MARK, nghttp2_is_fatal(rv)?
                          APLOG_ERR : APLOG_DEBUG, 0, session->c,
                          APLOGNO(02936) 
                          "h2_stream(%ld-%d): resuming stream %s",
                          session->id, stream->id, nghttp2_strerror(rv));
        }
    }
    return 1;
}

static int h2_session_resume_streams_with_data(h2_session *session) {
    AP_DEBUG_ASSERT(session);
    if (!h2_stream_set_is_empty(session->streams)
        && session->mplx && !session->aborted) {
        resume_ctx ctx;
        
        ctx.session      = session;
        ctx.resume_count = 0;

        /* Resume all streams where we have data in the out queue and
         * which had been suspended before. */
        h2_stream_set_iter(session->streams, resume_on_data, &ctx);
        return ctx.resume_count;
    }
    return 0;
}

h2_stream *h2_session_get_stream(h2_session *session, int stream_id)
{
    if (!session->last_stream || stream_id != session->last_stream->id) {
        session->last_stream = h2_stream_set_get(session->streams, stream_id);
    }
    return session->last_stream;
}

/* h2_io_on_read_cb implementation that offers the data read
 * directly to the session for consumption.
 */
static apr_status_t session_receive(const char *data, apr_size_t len,
                                    apr_size_t *readlen, int *done,
                                    void *puser)
{
    h2_session *session = (h2_session *)puser;
    AP_DEBUG_ASSERT(session);
    if (len > 0) {
        ssize_t n = nghttp2_session_mem_recv(session->ngh2,
                                             (const uint8_t *)data, len);
        if (n < 0) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, APR_EGENERAL,
                          session->c,
                          "h2_session: nghttp2_session_mem_recv error %d",
                          (int)n);
            if (nghttp2_is_fatal((int)n)) {
                *done = 1;
                h2_session_abort_int(session, (int)n);
                return APR_EGENERAL;
            }
        }
        else {
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
