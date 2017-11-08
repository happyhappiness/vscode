apr_pool_t *h2_worker_get_pool(h2_worker *worker)
{
    return worker->pool;
}