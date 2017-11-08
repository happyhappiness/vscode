apr_bucket_alloc_t *h2_worker_get_bucket_alloc(h2_worker *worker)
{
    return worker->bucket_alloc;
}