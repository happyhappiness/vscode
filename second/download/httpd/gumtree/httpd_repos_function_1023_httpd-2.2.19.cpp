static apr_ssize_t maxchild(cache_pqueue_t *q, apr_ssize_t i)
{
    apr_ssize_t child_node = left(i);

    if (child_node >= q->size)
        return 0;

    if ((child_node+1 < q->size) &&
        (q->pri(q->d[child_node+1]) > q->pri(q->d[child_node])))
    {
        child_node++; /* use right child instead of left */
    }

    return child_node;
}