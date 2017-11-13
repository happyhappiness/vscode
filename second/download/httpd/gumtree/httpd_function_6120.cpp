static apr_status_t h2_sos_mplx_readx(h2_sos *sos, h2_io_data_cb *cb, void *ctx,
                                      apr_off_t *plen, int *peos)
{
    h2_sos_mplx *msos = sos->ctx;
    apr_status_t status = APR_SUCCESS;
    
    status = h2_util_bb_readx(msos->bb, cb, ctx, plen, peos);
    if (status == APR_SUCCESS && !*peos && !*plen) {
        status = APR_EAGAIN;
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, msos->m->c,
                  "h2_stream(%ld-%d): readx, len=%ld eos=%d",
                  msos->m->id, sos->stream->id, (long)*plen, *peos);
    return status;
}