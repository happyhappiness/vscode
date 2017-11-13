apr_status_t h2_stream_read_to(h2_stream *stream, apr_bucket_brigade *bb, 
                               apr_off_t *plen, int *peos)
{
    apr_status_t status = APR_SUCCESS;
    apr_table_t *trailers = NULL;

    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream read_to_pre");
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    
    if (APR_BRIGADE_EMPTY(stream->bbout)) {
        apr_off_t tlen = *plen;
        int eos;
        status = h2_mplx_out_read_to(stream->session->mplx, stream->id, 
                                     stream->bbout, &tlen, &eos, &trailers);
    }
    
    if (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(stream->bbout)) {
        status = h2_transfer_brigade(bb, stream->bbout, stream->pool, 
                                     plen, peos);
    }
    else {
        *plen = 0;
        *peos = 0;
    }

    if (trailers && stream->response) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                      "h2_stream(%ld-%d): read_to, saving trailers",
                      stream->session->id, stream->id);
        h2_response_set_trailers(stream->response, trailers);
    }
    
    if (status == APR_SUCCESS && !*peos && !*plen) {
        status = APR_EAGAIN;
    }
    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream read_to_post");
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                  "h2_stream(%ld-%d): read_to, len=%ld eos=%d",
                  stream->session->id, stream->id, (long)*plen, *peos);
    return status;
}