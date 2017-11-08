h2_request *h2_request_create(int id, apr_pool_t *pool, 
                              apr_bucket_alloc_t *bucket_alloc)
{
    h2_request *req = apr_pcalloc(pool, sizeof(h2_request));
    if (req) {
        req->id = id;
        req->pool = pool;
        req->bucket_alloc = bucket_alloc;
    }
    return req;
}