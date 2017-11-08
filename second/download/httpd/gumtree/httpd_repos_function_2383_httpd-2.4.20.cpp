static h2_io *get_latest_repeatable_busy_unsubmitted_io(h2_mplx *m) 
{
    io_iter_ctx ctx;
    ctx.m = m;
    ctx.io = NULL;
    h2_io_set_iter(m->stream_ios, latest_repeatable_busy_unsubmitted_iter, &ctx);
    return ctx.io;
}