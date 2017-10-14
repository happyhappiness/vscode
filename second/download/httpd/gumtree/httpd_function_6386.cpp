apr_status_t h2_mplx_process(h2_mplx *m, int stream_id, 
                             const h2_request *req, 
                             h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    int do_registration = 0;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            h2_io *io = open_io(m, stream_id, req);
            
            if (!io->request->body) {
                status = h2_io_in_close(io);
            }
            
            m->need_registration = m->need_registration || h2_iq_empty(m->q);
            do_registration = (m->need_registration && m->workers_busy < m->workers_max);
            h2_iq_add(m->q, io->id, cmp, ctx);
            
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
                          "h2_mplx(%ld-%d): process", m->c->id, stream_id);
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_process");
        }
        leave_mutex(m, acquired);
    }
    if (status == APR_SUCCESS && do_registration) {
        workers_register(m);
    }
    return status;
}