apr_status_t h2_worker_destroy(h2_worker *worker)
{
    if (worker->thread) {
        apr_status_t status;
        apr_thread_join(&status, worker->thread);
        worker->thread = NULL;
    }
    if (worker->io) {
        apr_thread_cond_destroy(worker->io);
        worker->io = NULL;
    }
    if (worker->pool) {
        apr_pool_destroy(worker->pool);
        /* worker is gone */
    }
    return APR_SUCCESS;
}