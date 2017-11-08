apr_status_t cache_pq_insert(cache_pqueue_t *q, void *d)
{
    void *tmp;
    apr_ssize_t i;
    apr_ssize_t newsize;

    if (!q) return APR_EGENERAL;

    /* allocate more memory if necessary */
    if (q->size >= q->avail) {
        newsize = q->size + q->step;
        if (!(tmp = realloc(q->d, sizeof(void*) * newsize))) {
            return APR_EGENERAL;
        };
        q->d = tmp;
        q->avail = newsize;
    }

    /* insert item */
    i = q->size++;
    q->d[i] = d;
    cache_pq_bubble_up(q, i);
    return APR_SUCCESS;
}