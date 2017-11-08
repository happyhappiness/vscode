void h2_io_redo(h2_io *io)
{
    io->worker_started = 0;
    io->response = NULL;
    io->rst_error = 0;
    if (io->bbin) {
        apr_brigade_cleanup(io->bbin);
    }
    if (io->bbout) {
        apr_brigade_cleanup(io->bbout);
    }
    if (io->bbtmp) {
        apr_brigade_cleanup(io->bbtmp);
    }
    io->started_at = io->done_at = 0;
}