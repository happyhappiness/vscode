apr_status_t h2_worker_destroy(h2_worker *worker)
{
    if (worker->thread) {
        apr_status_t status;
        apr_thread_join(&status, worker->thread);
        worker->thread = NULL;
    }
    return APR_SUCCESS;
}