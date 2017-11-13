apr_status_t h2_stream_readx(h2_stream *stream, 
                             h2_io_data_cb *cb, void *ctx,
                             apr_off_t *plen, int *peos)
{
    apr_status_t status = APR_SUCCESS;
    apr_table_t *trailers = NULL;
    const char *src;
    
    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream readx_pre");
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    *peos = 0;
    if (!APR_BRIGADE_EMPTY(stream->bbout)) {
        apr_off_t origlen = *plen;
        
        src = "stream";
        status = h2_util_bb_readx(stream->bbout, cb, ctx, plen, peos);
        if (status == APR_SUCCESS && !*peos && !*plen) {
            apr_brigade_cleanup(stream->bbout);
            *plen = origlen;
            return h2_stream_readx(stream, cb, ctx, plen, peos);
        }
    }
    else {
        src = "mplx";
        status = h2_mplx_out_readx(stream->session->mplx, stream->id, 
                                   cb, ctx, plen, peos, &trailers);
    }
    
    if (trailers && stream->response) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                      "h2_stream(%ld-%d): readx, saving trailers",
                      stream->session->id, stream->id);
        h2_response_set_trailers(stream->response, trailers);
    }
    
    if (status == APR_SUCCESS && !*peos && !*plen) {
        status = APR_EAGAIN;
    }
    
    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream readx_post");
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                  "h2_stream(%ld-%d): readx %s, len=%ld eos=%d",
                  stream->session->id, stream->id, src, (long)*plen, *peos);
    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream readx_post");
    
    return status;
}