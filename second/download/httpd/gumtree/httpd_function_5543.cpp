static apr_status_t h2_sos_mplx_read_to(h2_sos *sos, apr_bucket_brigade *bb, 
                                        apr_off_t *plen, int *peos)
{
    h2_sos_mplx *msos = sos->ctx;
    apr_status_t status;

    status = h2_append_brigade(bb, msos->bb, plen, peos);
    if (status == APR_SUCCESS && !*peos && !*plen) {
        status = APR_EAGAIN;
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, msos->m->c,
                      "h2_stream(%ld-%d): read_to, len=%ld eos=%d",
                      msos->m->id, sos->stream->id, (long)*plen, *peos);
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, msos->m->c,
                  "h2_stream(%ld-%d): read_to, len=%ld eos=%d",
                  msos->m->id, sos->stream->id, (long)*plen, *peos);
    return status;
}