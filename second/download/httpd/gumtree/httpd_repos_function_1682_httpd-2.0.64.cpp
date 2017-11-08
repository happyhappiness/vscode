static int cache_pq_subtree_is_valid(cache_pqueue_t *q, int pos)
{
    if (left(pos) < q->size) {
        /* has a left child */
        if (q->pri(q->d[pos]) < q->pri(q->d[left(pos)]))
            return 0;
        if (!cache_pq_subtree_is_valid(q, left(pos)))
            return 0;
    }
    if (right(pos) < q->size) {
        /* has a right child */
        if (q->pri(q->d[pos]) < q->pri(q->d[right(pos)]))
            return 0;
        if (!cache_pq_subtree_is_valid(q, right(pos)))
            return 0;
    }
    return 1;
}