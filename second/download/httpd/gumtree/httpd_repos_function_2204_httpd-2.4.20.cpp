h2_task_queue *h2_tq_create(apr_pool_t *pool, int capacity)
{
    h2_task_queue *q = apr_pcalloc(pool, sizeof(h2_task_queue));
    if (q) {
        q->pool = pool;
        tq_grow(q, capacity);
        q->nelts = 0;
    }
    return q;
}