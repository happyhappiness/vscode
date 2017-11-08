h2_task_queue *h2_tq_create(long id, apr_pool_t *pool)
{
    h2_task_queue *q = apr_pcalloc(pool, sizeof(h2_task_queue));
    if (q) {
        q->id = id;
        APR_RING_ELEM_INIT(q, link);
        APR_RING_INIT(&q->tasks, h2_task, link);
    }
    return q;
}