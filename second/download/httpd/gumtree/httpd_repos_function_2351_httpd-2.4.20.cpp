static void io_destroy(h2_mplx *m, h2_io *io, int events)
{
    int reuse_slave;
    
    /* cleanup any buffered input */
    h2_io_in_shutdown(io);
    if (events) {
        /* Process outstanding events before destruction */
        io_in_consumed_signal(m, io);
    }
    
    /* The pool is cleared/destroyed which also closes all
     * allocated file handles. Give this count back to our
     * file handle pool. */
    m->tx_handles_reserved += io->files_handles_owned;

    h2_io_set_remove(m->stream_ios, io);
    h2_io_set_remove(m->ready_ios, io);
    if (m->redo_ios) {
        h2_io_set_remove(m->redo_ios, io);
    }

    reuse_slave = ((m->spare_slaves->nelts < m->spare_slaves->nalloc)
                    && !io->rst_error && io->eor);
    if (io->task) {
        conn_rec *slave = io->task->c;
        h2_task_destroy(io->task);
        io->task = NULL;
        
        if (reuse_slave && slave->keepalive == AP_CONN_KEEPALIVE) {
            apr_bucket_delete(io->eor);
            io->eor = NULL;
            APR_ARRAY_PUSH(m->spare_slaves, conn_rec*) = slave;
        }
        else {
            slave->sbh = NULL;
            h2_slave_destroy(slave, NULL);
        }
    }

    if (io->pool) {
        apr_pool_destroy(io->pool);
    }

    check_tx_free(m);
}