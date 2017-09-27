            return 1;
        default:
            return 0;
    }
}

static apr_status_t stream_pool_cleanup(void *ctx)
{
    h2_stream *stream = ctx;
    apr_status_t status;
    
    if (stream->input) {
        h2_beam_destroy(stream->input);
        stream->input = NULL;
    }
    if (stream->files) {
        apr_file_t *file;
        int i;
        for (i = 0; i < stream->files->nelts; ++i) {
            file = APR_ARRAY_IDX(stream->files, i, apr_file_t*);
            status = apr_file_close(file);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, stream->session->c, 
                          "h2_stream(%ld-%d): destroy, closed file %d", 
                          stream->session->id, stream->id, i);
        }
        stream->files = NULL;
    }
    return APR_SUCCESS;
}

h2_stream *h2_stream_open(int id, apr_pool_t *pool, h2_session *session,
                          int initiated_on, const h2_request *creq)
{
    h2_request *req;
    h2_stream *stream = apr_pcalloc(pool, sizeof(h2_stream));
    
    stream->id        = id;
    stream->state     = H2_STREAM_ST_IDLE;
    stream->pool      = pool;
    stream->session   = session;
    set_state(stream, H2_STREAM_ST_OPEN);
    
    if (creq) {
        /* take it into out pool and assure correct id's */
        req = h2_request_clone(pool, creq);
        req->id = id;
        req->initiated_on = initiated_on;
    }
    else {
        req = h2_req_create(id, pool, 
                h2_config_geti(session->config, H2_CONF_SER_HEADERS));
    }
    stream->request = req; 
    
    apr_pool_cleanup_register(pool, stream, stream_pool_cleanup, 
                              apr_pool_cleanup_null);
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03082)
                  "h2_stream(%ld-%d): opened", session->id, stream->id);
    return stream;
}

void h2_stream_cleanup(h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    if (stream->buffer) {
        apr_brigade_cleanup(stream->buffer);
    }
    if (stream->input) {
        apr_status_t status;
        status = h2_beam_shutdown(stream->input, APR_NONBLOCK_READ, 1);
        if (status == APR_EAGAIN) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c, 
                          "h2_stream(%ld-%d): wait on input shutdown", 
                          stream->session->id, stream->id);
            status = h2_beam_shutdown(stream->input, APR_BLOCK_READ, 1);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c, 
                          "h2_stream(%ld-%d): input shutdown returned", 
                          stream->session->id, stream->id);
        }
    }
}

void h2_stream_destroy(h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, stream->session->c, 
                  "h2_stream(%ld-%d): destroy", 
                  stream->session->id, stream->id);
    if (stream->pool) {
        apr_pool_destroy(stream->pool);
    }
}

void h2_stream_eos_destroy(h2_stream *stream)
{
    h2_session_stream_done(stream->session, stream);
    /* stream possibly destroyed */
}

apr_pool_t *h2_stream_detach_pool(h2_stream *stream)
{
    apr_pool_t *pool = stream->pool;
    stream->pool = NULL;
