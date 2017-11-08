static h2_io *get_timed_out_busy_stream(h2_mplx *m) 
{
    io_iter_ctx ctx;
    ctx.m = m;
    ctx.io = NULL;
    ctx.now = apr_time_now();
    h2_io_set_iter(m->stream_ios, timed_out_busy_iter, &ctx);
    return ctx.io;
}