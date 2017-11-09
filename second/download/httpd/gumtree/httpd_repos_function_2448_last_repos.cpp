apr_status_t h2_mplx_reprioritize(h2_mplx *m, h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    
    H2_MPLX_ENTER(m);

    if (m->aborted) {
        status = APR_ECONNABORTED;
    }
    else {
        h2_iq_sort(m->q, cmp, ctx);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                      "h2_mplx(%ld): reprioritize tasks", m->id);
        status = APR_SUCCESS;
    }

    H2_MPLX_LEAVE(m);
    return status;
}