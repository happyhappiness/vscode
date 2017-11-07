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