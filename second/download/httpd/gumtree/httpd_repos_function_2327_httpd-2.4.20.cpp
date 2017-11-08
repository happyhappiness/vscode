h2_int_queue *h2_iq_create(apr_pool_t *pool, int capacity)
{
    h2_int_queue *q = apr_pcalloc(pool, sizeof(h2_int_queue));
    if (q) {
        q->pool = pool;
        tq_grow(q, capacity);
        q->nelts = 0;
    }
    return q;
}