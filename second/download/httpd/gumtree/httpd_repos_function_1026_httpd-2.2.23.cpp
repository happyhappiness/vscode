static void cache_pq_percolate_down(cache_pqueue_t *q, apr_ssize_t i)
{
    apr_ssize_t child_node;
    void *moving_node = q->d[i];
    long moving_pri = q->pri(moving_node);

    while ((child_node = maxchild(q, i)) &&
           (moving_pri < q->pri(q->d[child_node])))
    {
        q->d[i] = q->d[child_node];
        q->set(q->d[i], i);
        i = child_node;
    }

    q->d[i] = moving_node;
    q->set(moving_node, i);
}