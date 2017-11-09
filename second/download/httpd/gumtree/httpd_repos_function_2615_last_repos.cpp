h2_proxy_iqueue *h2_proxy_iq_create(apr_pool_t *pool, int capacity)
{
    h2_proxy_iqueue *q = apr_pcalloc(pool, sizeof(h2_proxy_iqueue));
    if (q) {
        q->pool = pool;
        iq_grow(q, capacity);
        q->nelts = 0;
    }
    return q;
}