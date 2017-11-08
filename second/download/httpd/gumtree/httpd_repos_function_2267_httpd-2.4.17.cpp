static void stream_destroy(h2_mplx *m, h2_stream *stream, h2_io *io)
{
    apr_pool_t *pool = h2_stream_detach_pool(stream);
    if (pool) {
        apr_pool_clear(pool);
        if (m->spare_pool) {
            apr_pool_destroy(m->spare_pool);
        }
        m->spare_pool = pool;
    }
    h2_stream_destroy(stream);
    if (io) {
        /* The pool is cleared/destroyed which also closes all
         * allocated file handles. Give this count back to our
         * file handle pool. */
        m->file_handles_allowed += io->files_handles_owned;
        h2_io_set_remove(m->stream_ios, io);
        h2_io_set_remove(m->ready_ios, io);
        h2_io_destroy(io);
    }
}