static int stream_done_iter(void *ctx, h2_io *io) {
    return io_stream_done((h2_mplx*)ctx, io, 0);
}