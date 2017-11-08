int cache_pq_is_valid(cache_pqueue_t *q)
{
    return cache_pq_subtree_is_valid(q, 1);
}