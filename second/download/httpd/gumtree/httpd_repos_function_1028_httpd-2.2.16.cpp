void *cache_pq_pop(cache_pqueue_t *q)
{
    void *head;

    if (!q || q->size == 1)
        return NULL;

    head = q->d[1];
    q->d[1] = q->d[--q->size];
    cache_pq_percolate_down(q, 1);

    return head;
}