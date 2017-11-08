static apr_status_t skiplisti_init(apr_skiplist **s, apr_pool_t *p)
{
    apr_skiplist *sl;
    if (p) {
        sl = apr_pcalloc(p, sizeof(apr_skiplist));
        sl->memlist = apr_array_make(p, 20, sizeof(memlist_t));
    }
    else {
        sl = calloc(1, sizeof(apr_skiplist));
    }
#if 0
    sl->compare = (apr_skiplist_compare) NULL;
    sl->comparek = (apr_skiplist_compare) NULL;
    sl->height = 0;
    sl->preheight = 0;
    sl->size = 0;
    sl->top = NULL;
    sl->bottom = NULL;
    sl->index = NULL;
#endif
    sl->pool = p;
    *s = sl;
    return APR_SUCCESS;
}