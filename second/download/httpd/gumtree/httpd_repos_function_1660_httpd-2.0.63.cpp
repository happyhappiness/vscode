cache_pqueue_t *cache_pq_init(apr_ssize_t n,
                              cache_pqueue_get_priority pri,
                              cache_pqueue_getpos get,
                              cache_pqueue_setpos set)
{
    cache_pqueue_t *q;

    if (!(q = malloc(sizeof(cache_pqueue_t)))) {
        return NULL;
    }

    /* Need to allocate n+1 elements since element 0 isn't used. */
    if (!(q->d = malloc(sizeof(void*) * (n+1)))) {
        free(q);
        return NULL;
    }
    q->avail = q->step = (n+1);  /* see comment above about n+1 */
    q->pri = pri;
    q->size = 1;
    q->get = get;
    q->set = set;
    return q;
}