apr_status_t h2_io_signal_wait(h2_mplx *m, h2_io *io)
{
    apr_status_t status;
    
    if (io->timeout_at != 0) {
        status = apr_thread_cond_timedwait(io->timed_cond, m->lock, io->timeout_at);
        if (APR_STATUS_IS_TIMEUP(status)) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, m->c, APLOGNO(03055)  
                          "h2_mplx(%ld-%d): stream timeout expired: %s",
                          m->id, io->id, 
                          (io->timed_op == H2_IO_READ)? "read" : "write");
            h2_io_rst(io, H2_ERR_CANCEL);
        }
    }
    else {
        apr_thread_cond_wait(io->timed_cond, m->lock);
        status = APR_SUCCESS;
    }
    if (io->orphaned && status == APR_SUCCESS) {
        return APR_ECONNABORTED;
    }
    return status;
}