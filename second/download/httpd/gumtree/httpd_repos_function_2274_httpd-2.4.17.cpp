apr_status_t h2_mplx_in_update_windows(h2_mplx *m, 
                                       h2_mplx_consumed_cb *cb, void *cb_ctx)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        update_ctx ctx;
        
        ctx.cb              = cb;
        ctx.cb_ctx          = cb_ctx;
        ctx.streams_updated = 0;

        status = APR_EAGAIN;
        h2_io_set_iter(m->stream_ios, update_window, &ctx);
        
        if (ctx.streams_updated) {
            status = APR_SUCCESS;
        }
        apr_thread_mutex_unlock(m->lock);
    }
    return status;
}