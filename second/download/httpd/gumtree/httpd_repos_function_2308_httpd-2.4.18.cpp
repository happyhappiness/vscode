static void io_destroy(h2_mplx *m, h2_io *io, int events)
{
    apr_pool_t *pool = io->pool;
    
    /* cleanup any buffered input */
    h2_io_in_shutdown(io);
    if (events) {
        /* Process outstanding events before destruction */
        io_process_events(m, io);
    }
    
    io->pool = NULL;    
    /* The pool is cleared/destroyed which also closes all
     * allocated file handles. Give this count back to our
     * file handle pool. */
    m->file_handles_allowed += io->files_handles_owned;
    h2_io_set_remove(m->stream_ios, io);
    h2_io_set_remove(m->ready_ios, io);
    h2_io_destroy(io);
    
    if (pool) {
        apr_pool_clear(pool);
        if (m->spare_pool) {
            apr_pool_destroy(m->spare_pool);
        }
        m->spare_pool = pool;
    }
}