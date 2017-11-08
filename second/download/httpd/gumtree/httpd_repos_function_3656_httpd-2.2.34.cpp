static apr_status_t skiplist_free_node(apr_skiplist *sl, apr_skiplistnode *m)
{
    return skiplist_qpush(&sl->nodes_q, m);
}