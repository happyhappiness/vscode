static apr_skiplistnode *skiplist_new_node(apr_skiplist *sl)
{
    apr_skiplistnode *m = skiplist_qpop(&sl->nodes_q);
    if (!m) {
        if (sl->pool) {
            m = apr_palloc(sl->pool, sizeof *m);
        }
        else {
            m = malloc(sizeof *m);
        }
    }
    return m;
}