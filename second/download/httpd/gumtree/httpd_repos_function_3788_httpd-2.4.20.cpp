static void eor_bucket_destroy(void *data)
{
    request_rec *r = (request_rec *)data;

    if (r) {
        /* eor_bucket_cleanup will be called when the pool gets destroyed */
        apr_pool_destroy(r->pool);
    }
}