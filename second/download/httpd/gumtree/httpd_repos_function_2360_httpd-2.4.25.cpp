apr_status_t h2_mplx_stream_do(h2_mplx *m, h2_mplx_stream_cb *cb, void *ctx)
{
    apr_status_t status;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        stream_iter_ctx_t x;
        x.cb = cb;
        x.ctx = ctx;
        h2_ihash_iter(m->streams, stream_iter_wrap, &x);
        
        leave_mutex(m, acquired);
    }
    return status;
}