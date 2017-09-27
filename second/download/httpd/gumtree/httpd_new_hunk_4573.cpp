}

apr_status_t h2_stream_add_header(h2_stream *stream,
                                  const char *name, size_t nlen,
                                  const char *value, size_t vlen)
{
    h2_session *session = stream->session;
    int error = 0;
    apr_status_t status;
    
    if (stream->has_response) {
        return APR_EINVAL;    
    }
    ++stream->request_headers_added;
    if (name[0] == ':') {
        if ((vlen) > session->s->limit_req_line) {
            /* pseudo header: approximation of request line size check */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          H2_STRM_MSG(stream, "pseudo %s too long"), name);
            error = HTTP_REQUEST_URI_TOO_LARGE;
        }
    }
    else if ((nlen + 2 + vlen) > session->s->limit_req_fieldsize) {
        /* header too long */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                      H2_STRM_MSG(stream, "header %s too long"), name);
        error = HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE;
    }
    
    if (stream->request_headers_added > session->s->limit_req_fields + 4) {
        /* too many header lines, include 4 pseudo headers */
        if (stream->request_headers_added 
            > session->s->limit_req_fields + 4 + 100) {
            /* yeah, right */
            h2_stream_rst(stream, H2_ERR_ENHANCE_YOUR_CALM);
            return APR_ECONNRESET;
        }
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                      H2_STRM_MSG(stream, "too many header lines")); 
        error = HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE;
    }
    
    if (error) {
        set_error_response(stream, error);
        return APR_EINVAL; 
    }
    else if (H2_SS_IDLE == stream->state) {
        if (!stream->rtmp) {
            stream->rtmp = h2_req_create(stream->id, stream->pool, 
                                         NULL, NULL, NULL, NULL, NULL, 0);
        }
        status = h2_request_add_header(stream->rtmp, stream->pool,
                                       name, nlen, value, vlen);
    }
    else  {
        status = add_trailer(stream, name, nlen, value, vlen);
    }
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                      H2_STRM_MSG(stream, "header %s not accepted"), name);
        h2_stream_dispatch(stream, H2_SEV_CANCELLED);
    }
    return status;
}

static apr_bucket *get_first_headers_bucket(apr_bucket_brigade *bb)
{
    if (bb) {
        apr_bucket *b = APR_BRIGADE_FIRST(bb);
        while (b != APR_BRIGADE_SENTINEL(bb)) {
            if (H2_BUCKET_IS_HEADERS(b)) {
                return b;
            }
            b = APR_BUCKET_NEXT(b);
        }
    }
    return NULL;
}

static apr_status_t add_data(h2_stream *stream, apr_off_t requested,
                             apr_off_t *plen, int *peos, int *complete, 
                             h2_headers **pheaders)
{
    apr_bucket *b, *e;
    
    *peos = 0;
    *plen = 0;
    *complete = 0;
    if (pheaders) {
        *pheaders = NULL;
    }

    H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "add_data");
    b = APR_BRIGADE_FIRST(stream->out_buffer);
    while (b != APR_BRIGADE_SENTINEL(stream->out_buffer)) {
        e = APR_BUCKET_NEXT(b);
        if (APR_BUCKET_IS_METADATA(b)) {
            if (APR_BUCKET_IS_FLUSH(b)) {
                APR_BUCKET_REMOVE(b);
                apr_bucket_destroy(b);
            }
            else if (APR_BUCKET_IS_EOS(b)) {
                *peos = 1;
                return APR_SUCCESS;
            }
            else if (H2_BUCKET_IS_HEADERS(b)) {
                if (*plen > 0) {
                    /* data before the response, can only return up to here */
                    return APR_SUCCESS;
                }
                else if (pheaders) {
                    *pheaders = h2_bucket_headers_get(b);
                    APR_BUCKET_REMOVE(b);
                    apr_bucket_destroy(b);
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                                  H2_STRM_MSG(stream, "prep, -> response %d"), 
                                  (*pheaders)->status);
                    return APR_SUCCESS;
                }
                else {
                    return APR_EAGAIN;
                }
            }
        }
        else if (b->length == 0) {
            APR_BUCKET_REMOVE(b);
            apr_bucket_destroy(b);
        }
        else {
            ap_assert(b->length != (apr_size_t)-1);
            *plen += b->length;
            if (*plen >= requested) {
                *plen = requested;
                return APR_SUCCESS;
            }
        }
        b = e;
    }
    *complete = 1;
    return APR_SUCCESS;
}

apr_status_t h2_stream_out_prepare(h2_stream *stream, apr_off_t *plen, 
                                   int *peos, h2_headers **pheaders)
{
    apr_status_t status = APR_SUCCESS;
    apr_off_t requested, missing, max_chunk = H2_DATA_CHUNK_SIZE;
    conn_rec *c;
    int complete;

    ap_assert(stream);
    
    if (stream->rst_error) {
        *plen = 0;
        *peos = 1;
        return APR_ECONNRESET;
    }
    
    c = stream->session->c;
    prep_output(stream);

    /* determine how much we'd like to send. We cannot send more than
     * is requested. But we can reduce the size in case the master
     * connection operates in smaller chunks. (TSL warmup) */
    if (stream->session->io.write_size > 0) {
        max_chunk = stream->session->io.write_size - 9; /* header bits */ 
    }
    requested = (*plen > 0)? H2MIN(*plen, max_chunk) : max_chunk;
    
    /* count the buffered data until eos or a headers bucket */
    status = add_data(stream, requested, plen, peos, &complete, pheaders);
    
    if (status == APR_EAGAIN) {
        /* TODO: ugly, someone needs to retrieve the response first */
        h2_mplx_keep_active(stream->session->mplx, stream);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      H2_STRM_MSG(stream, "prep, response eagain"));
        return status;
    }
    else if (status != APR_SUCCESS) {
        return status;
    }
    
    if (pheaders && *pheaders) {
        return APR_SUCCESS;
    }
    
    missing = H2MIN(requested, stream->max_mem) - *plen;
    if (complete && !*peos && missing > 0) {
        if (stream->output) {
            H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "pre");
            status = h2_beam_receive(stream->output, stream->out_buffer, 
                                     APR_NONBLOCK_READ, 
                                     stream->max_mem - *plen);
            H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "post");
        }
        else {
            status = APR_EOF;
        }
        
        if (APR_STATUS_IS_EOF(status)) {
            apr_bucket *eos = apr_bucket_eos_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(stream->out_buffer, eos);
            *peos = 1;
            status = APR_SUCCESS;
        }
        else if (status == APR_SUCCESS) {
            /* do it again, now that we have gotten more */
            status = add_data(stream, requested, plen, peos, &complete, pheaders);
        }
    }
    
    if (status == APR_SUCCESS) {
        if (*peos || *plen) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                          H2_STRM_MSG(stream, "prepare, len=%ld eos=%d"),
                          (long)*plen, *peos);
        }
        else {
            status = APR_EAGAIN;
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                          H2_STRM_MSG(stream, "prepare, no data"));
        }
    }
    return status;
}

static int is_not_headers(apr_bucket *b)
{
    return !H2_BUCKET_IS_HEADERS(b);
