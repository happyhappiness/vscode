apr_status_t h2_mplx_in_update_windows(h2_mplx *m)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        update_ctx ctx;
        
        ctx.m               = m;
        ctx.streams_updated = 0;

        status = APR_EAGAIN;
        h2_io_set_iter(m->stream_ios, update_window, &ctx);
        
        if (ctx.streams_updated) {
            status = APR_SUCCESS;
        }
        leave_mutex(m, acquired);
    }
    return status;
}