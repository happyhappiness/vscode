static void cache_pq_bubble_up(cache_pqueue_t *q, apr_ssize_t i)
{
    apr_ssize_t parent_node;
    void *moving_node = q->d[i];
    long moving_pri = q->pri(moving_node);

    for (parent_node = parent(i);
         ((i > 1) && (q->pri(q->d[parent_node]) < moving_pri));
         i = parent_node, parent_node = parent(i))
    {
        q->d[i] = q->d[parent_node];
        q->set(q->d[i], i);
    }

    q->d[i] = moving_node;
    q->set(moving_node, i);
}