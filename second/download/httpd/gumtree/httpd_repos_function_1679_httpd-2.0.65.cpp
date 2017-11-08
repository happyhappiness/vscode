void cache_pq_change_priority(cache_pqueue_t *q,
                              long old_priority,
                              long new_priority,
                              void *d)
{
    apr_ssize_t posn;

    posn = q->get(d);
    if (new_priority > old_priority)
        cache_pq_bubble_up(q, posn);
    else
        cache_pq_percolate_down(q, posn);
}