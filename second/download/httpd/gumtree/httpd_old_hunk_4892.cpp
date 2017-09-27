/*
 * Create an already defined worker and free up memory
 */
PROXY_DECLARE(apr_status_t) ap_proxy_share_worker(proxy_worker *worker, proxy_worker_shared *shm,
                                                  int i)
{
    if (!shm || !worker->s)
        return APR_EINVAL;

    memcpy(shm, worker->s, sizeof(proxy_worker_shared));
    if (worker->s->was_malloced)
        free(worker->s); /* was malloced in ap_proxy_define_worker */
    worker->s = shm;
    worker->s->index = i;
    return APR_SUCCESS;
}

PROXY_DECLARE(apr_status_t) ap_proxy_initialize_worker(proxy_worker *worker, server_rec *s, apr_pool_t *p)
