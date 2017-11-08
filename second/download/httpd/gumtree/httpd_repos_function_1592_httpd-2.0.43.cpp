cache_pqueue_t *cache_pq_init(apr_ssize_t n,
                              cache_pqueue_get_priority pri,
                              cache_pqueue_getpos get,
                              cache_pqueue_setpos set)
{
    cache_pqueue_t *q;

    if (!(q = malloc(sizeof(cache_pqueue_t)))) {
        return NULL;
    }

    if (!(q->d = malloc(sizeof(void*) * n))) {
        free(q);
        return NULL;
    }
    q->avail = q->step = n;
    q->pri = pri;
    q->size = 1;
    q->get = get;
    q->set = set;
    return q;
}