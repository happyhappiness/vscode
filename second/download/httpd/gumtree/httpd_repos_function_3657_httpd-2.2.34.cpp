static apr_status_t skiplisti_init(apr_skiplist **s, apr_pool_t *p)
{
    apr_skiplist *sl;
    if (p) {
        sl = apr_pcalloc(p, sizeof(apr_skiplist));
        sl->memlist = apr_array_make(p, 20, sizeof(memlist_t));
        sl->pool = sl->nodes_q.p = sl->stack_q.p = p;
    }
    else {
        sl = calloc(1, sizeof(apr_skiplist));
        if (!sl) {
            return APR_ENOMEM;
        }
    }
    *s = sl;
    return APR_SUCCESS;
}