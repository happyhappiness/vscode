static int stream_done_iter(void *ctx, void *val)
{
    stream_done((h2_mplx*)ctx, val, 0);
    return 0;
}