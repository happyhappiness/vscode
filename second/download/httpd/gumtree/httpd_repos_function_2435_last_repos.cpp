apr_status_t h2_mplx_stream_do(h2_mplx *m, h2_mplx_stream_cb *cb, void *ctx)
{
    stream_iter_ctx_t x;
    
    H2_MPLX_ENTER(m);

    x.cb = cb;
    x.ctx = ctx;
    h2_ihash_iter(m->streams, stream_iter_wrap, &x);
        
    H2_MPLX_LEAVE(m);
    return APR_SUCCESS;
}