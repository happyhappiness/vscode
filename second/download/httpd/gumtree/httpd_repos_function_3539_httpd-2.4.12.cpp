static void clean_child_exit(int code, int worker_num, apr_pool_t *ptrans,
                             apr_bucket_alloc_t *bucket_alloc)
{
    apr_bucket_alloc_destroy(bucket_alloc);
    if (!shutdown_pending) {
        apr_pool_destroy(ptrans);
    }

    atomic_dec (&worker_thread_count);
    if (worker_num >=0)
        ap_update_child_status_from_indexes(0, worker_num, WORKER_DEAD,
                                            (request_rec *) NULL);
    NXThreadExit((void*)&code);
}