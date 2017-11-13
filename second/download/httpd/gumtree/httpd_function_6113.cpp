apr_status_t h2_stream_prep_read(h2_stream *stream, 
                                 apr_off_t *plen, int *peos)
{
    apr_status_t status = APR_SUCCESS;
    const char *src;
    apr_table_t *trailers = NULL;
    int test_read = (*plen == 0);
    
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }

    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream prep_read_pre");
    if (!APR_BRIGADE_EMPTY(stream->bbout)) {
        src = "stream";
        status = h2_util_bb_avail(stream->bbout, plen, peos);
        if (!test_read && status == APR_SUCCESS && !*peos && !*plen) {
            apr_brigade_cleanup(stream->bbout);
            return h2_stream_prep_read(stream, plen, peos);
        }
        trailers = stream->response? stream->response->trailers : NULL;
    }
    else {
        src = "mplx";
        status = h2_mplx_out_readx(stream->session->mplx, stream->id, 
                                   NULL, NULL, plen, peos, &trailers);
        if (trailers && stream->response) {
            h2_response_set_trailers(stream->response, trailers);
        }    
    }
    
    if (!test_read && status == APR_SUCCESS && !*peos && !*plen) {
        status = APR_EAGAIN;
    }
    
    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream prep_read_post");
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                  "h2_stream(%ld-%d): prep_read %s, len=%ld eos=%d, trailers=%s",
                  stream->session->id, stream->id, src, (long)*plen, *peos,
                  trailers? "yes" : "no");
    return status;
}