apr_status_t h2_stream_prep_read(h2_stream *stream, 
                                 apr_size_t *plen, int *peos)
{
    apr_status_t status = APR_SUCCESS;
    const char *src;
    
    if (stream->bbout && !APR_BRIGADE_EMPTY(stream->bbout)) {
        src = "stream";
        status = h2_util_bb_avail(stream->bbout, plen, peos);
        if (status == APR_SUCCESS && !*peos && !*plen) {
            apr_brigade_cleanup(stream->bbout);
            return h2_stream_prep_read(stream, plen, peos);
        }
    }
    else {
        src = "mplx";
        status = h2_mplx_out_readx(stream->m, stream->id, 
                                   NULL, NULL, plen, peos);
    }
    if (status == APR_SUCCESS && !*peos && !*plen) {
        status = APR_EAGAIN;
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->m->c,
                  "h2_stream(%ld-%d): prep_read %s, len=%ld eos=%d",
                  stream->m->id, stream->id, 
                  src, (long)*plen, *peos);
    return status;
}