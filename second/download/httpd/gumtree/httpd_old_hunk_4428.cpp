            }
        }
    }
    return status;
}

apr_status_t h2_stream_set_response(h2_stream *stream, h2_response *response,
                                    h2_bucket_beam *output)
{
    apr_status_t status = APR_SUCCESS;
    conn_rec *c = stream->session->c;
    
    if (!output_open(stream)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "h2_stream(%ld-%d): output closed", 
                      stream->session->id, stream->id);
        return APR_ECONNRESET;
    }
    
    stream->response = response;
    stream->output = output;
    stream->buffer = apr_brigade_create(stream->pool, c->bucket_alloc);
    
    h2_stream_filter(stream);
    if (stream->output) {
        status = fill_buffer(stream, 0);
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
                  "h2_stream(%ld-%d): set_response(%d)", 
                  stream->session->id, stream->id, 
                  stream->response->http_status);
    return status;
}

apr_status_t h2_stream_set_error(h2_stream *stream, int http_status)
{
    h2_response *response;
    
    if (stream->submitted) {
        return APR_EINVAL;
    }
    response = h2_response_die(stream->id, http_status, stream->request, 
                               stream->pool);
    return h2_stream_set_response(stream, response, NULL);
}

static const apr_size_t DATA_CHUNK_SIZE = ((16*1024) - 100 - 9); 

apr_status_t h2_stream_out_prepare(h2_stream *stream,
                                   apr_off_t *plen, int *peos)
{
    conn_rec *c = stream->session->c;
    apr_status_t status = APR_SUCCESS;
    apr_off_t requested;

    if (stream->rst_error) {
        *plen = 0;
        *peos = 1;
        return APR_ECONNRESET;
    }

    if (*plen > 0) {
        requested = H2MIN(*plen, DATA_CHUNK_SIZE);
    }
    else {
        requested = DATA_CHUNK_SIZE;
    }
    *plen = requested;
    
    H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "h2_stream_out_prepare_pre");
    h2_util_bb_avail(stream->buffer, plen, peos);
    if (!*peos && *plen < requested) {
        /* try to get more data */
        status = fill_buffer(stream, (requested - *plen) + DATA_CHUNK_SIZE);
        if (APR_STATUS_IS_EOF(status)) {
            apr_bucket *eos = apr_bucket_eos_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(stream->buffer, eos);
            status = APR_SUCCESS;
        }
        else if (status == APR_EAGAIN) {
            /* did not receive more, it's ok */
            status = APR_SUCCESS;
        }
        *plen = requested;
        h2_util_bb_avail(stream->buffer, plen, peos);
    }
    H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "h2_stream_out_prepare_post");
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
                  "h2_stream(%ld-%d): prepare, len=%ld eos=%d, trailers=%s",
                  c->id, stream->id, (long)*plen, *peos,
                  (stream->response && stream->response->trailers)? 
                  "yes" : "no");
    if (!*peos && !*plen && status == APR_SUCCESS) {
        return APR_EAGAIN;
    }
    return status;
}


apr_status_t h2_stream_read_to(h2_stream *stream, apr_bucket_brigade *bb, 
                               apr_off_t *plen, int *peos)
{
    conn_rec *c = stream->session->c;
    apr_status_t status = APR_SUCCESS;

    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    status = h2_append_brigade(bb, stream->buffer, plen, peos);
    if (status == APR_SUCCESS && !*peos && !*plen) {
        status = APR_EAGAIN;
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, c,
                  "h2_stream(%ld-%d): read_to, len=%ld eos=%d",
                  c->id, stream->id, (long)*plen, *peos);
