static apr_status_t h2_sos_mplx_prepare(h2_sos *sos, apr_off_t *plen, int *peos)
{
    h2_sos_mplx *msos = sos->ctx;
    apr_status_t status = APR_SUCCESS;
    
    H2_SOS_MPLX_OUT(APLOG_TRACE2, msos, "h2_sos_mplx prepare_pre");
    
    if (APR_BRIGADE_EMPTY(msos->bb)) {
        status = mplx_transfer(msos, sos->stream->id, sos->stream->pool);
    }
    h2_util_bb_avail(msos->bb, plen, peos);
    
    H2_SOS_MPLX_OUT(APLOG_TRACE2, msos, "h2_sos_mplx prepare_post");
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, msos->m->c,
                  "h2_stream(%ld-%d): prepare, len=%ld eos=%d, trailers=%s",
                  msos->m->id, sos->stream->id, (long)*plen, *peos,
                  msos->trailers? "yes" : "no");
    if (!*peos && !*plen) {
        status = APR_EAGAIN;
    }
    
    return status;
}