apr_status_t h2_stream_out_prepare(h2_stream *stream, apr_off_t *plen, 
                                   int *peos, h2_headers **presponse)
{
    conn_rec *c = stream->session->c;
    apr_status_t status = APR_SUCCESS;
    apr_off_t requested;
    apr_bucket *b, *e;

    if (presponse) {
        *presponse = NULL;
    }
    
    if (stream->rst_error) {
        *plen = 0;
        *peos = 1;
        return APR_ECONNRESET;
    }
    
    if (!output_open(stream)) {
        return APR_ECONNRESET;
    }
    prep_output(stream);

    if (*plen > 0) {
        requested = H2MIN(*plen, H2_DATA_CHUNK_SIZE);
    }
    else {
        requested = H2_DATA_CHUNK_SIZE;
    }
    *plen = requested;
    
    H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "h2_stream_out_prepare_pre");
    h2_util_bb_avail(stream->out_buffer, plen, peos);
    if (!*peos && *plen < requested) {
        /* try to get more data */
        status = fill_buffer(stream, (requested - *plen) + H2_DATA_CHUNK_SIZE);
        if (APR_STATUS_IS_EOF(status)) {
            apr_bucket *eos = apr_bucket_eos_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(stream->out_buffer, eos);
            status = APR_SUCCESS;
        }
        else if (status == APR_EAGAIN) {
            /* did not receive more, it's ok */
            status = APR_SUCCESS;
        }
        *plen = requested;
        h2_util_bb_avail(stream->out_buffer, plen, peos);
    }
    H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "h2_stream_out_prepare_post");
    
    b = APR_BRIGADE_FIRST(stream->out_buffer);
    while (b != APR_BRIGADE_SENTINEL(stream->out_buffer)) {
        e = APR_BUCKET_NEXT(b);
        if (APR_BUCKET_IS_FLUSH(b)
            || (!APR_BUCKET_IS_METADATA(b) && b->length == 0)) {
            APR_BUCKET_REMOVE(b);
            apr_bucket_destroy(b);
        }
        else {
            break;
        }
        b = e;
    }
    
    b = get_first_headers_bucket(stream->out_buffer);
    if (b) {
        /* there are HEADERS to submit */
        *peos = 0;
        *plen = 0;
        if (b == APR_BRIGADE_FIRST(stream->out_buffer)) {
            if (presponse) {
                *presponse = h2_bucket_headers_get(b);
                APR_BUCKET_REMOVE(b);
                apr_bucket_destroy(b);
                status = APR_SUCCESS;
            }
            else {
                /* someone needs to retrieve the response first */
                h2_mplx_keep_active(stream->session->mplx, stream->id);
                status = APR_EAGAIN;
            }
        }
        else {
            apr_bucket *e = APR_BRIGADE_FIRST(stream->out_buffer);
            while (e != APR_BRIGADE_SENTINEL(stream->out_buffer)) {
                if (e == b) {
                    break;
                }
                else if (e->length != (apr_size_t)-1) {
                    *plen += e->length;
                }
                e = APR_BUCKET_NEXT(e);
            }
        }
    }
    
    if (!*peos && !*plen && status == APR_SUCCESS 
        && (!presponse || !*presponse)) {
        status = APR_EAGAIN;
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
                  "h2_stream(%ld-%d): prepare, len=%ld eos=%d",
                  c->id, stream->id, (long)*plen, *peos);
    return status;
}