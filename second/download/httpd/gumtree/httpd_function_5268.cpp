apr_status_t h2_mplx_process(h2_mplx *m, int stream_id,
                             const h2_request *req, int eos, 
                             h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_io *io = open_io(m, stream_id);
        io->request = req;
        io->request_body = !eos;

        if (eos) {
            status = h2_io_in_close(io);
        }
        
        h2_tq_add(m->q, io->id, cmp, ctx);

        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
                      "h2_mplx(%ld-%d): process", m->c->id, stream_id);
        H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_process");
        apr_thread_mutex_unlock(m->lock);
    }
    
    if (status == APR_SUCCESS) {
        workers_register(m);
    }
    return status;
}