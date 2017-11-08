void cache_pq_free(cache_pqueue_t *q)
{
    free(q->d);
    free(q);
}