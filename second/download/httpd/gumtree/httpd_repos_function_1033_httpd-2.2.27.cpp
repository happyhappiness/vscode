apr_status_t cache_pq_remove(cache_pqueue_t *q, void *d)
{
    apr_ssize_t posn = q->get(d);
    q->d[posn] = q->d[--q->size];
    if (q->pri(q->d[posn]) > q->pri(d))
        cache_pq_bubble_up(q, posn);
    else
        cache_pq_percolate_down(q, posn);

    return APR_SUCCESS;
}