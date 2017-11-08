static apr_status_t ngn_out_update_windows(h2_mplx *m, h2_req_engine *ngn)
{
    ngn_update_ctx ctx;
        
    ctx.m = m;
    ctx.ngn = ngn;
    ctx.streams_updated = 0;
    h2_io_set_iter(m->stream_ios, ngn_update_window, &ctx);
    
    return ctx.streams_updated? APR_SUCCESS : APR_EAGAIN;
}