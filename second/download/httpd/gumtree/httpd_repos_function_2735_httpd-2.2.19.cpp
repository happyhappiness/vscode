static struct apr_thread_list_elt *elt_new(apr_thread_pool_t * me,
                                           apr_thread_t * t)
{
    struct apr_thread_list_elt *elt;

    if (APR_RING_EMPTY(me->recycled_thds, apr_thread_list_elt, link)) {
        elt = apr_pcalloc(me->pool, sizeof(*elt));
        if (NULL == elt) {
            return NULL;
        }
    }
    else {
        elt = APR_RING_FIRST(me->recycled_thds);
        APR_RING_REMOVE(elt, link);
    }

    APR_RING_ELEM_INIT(elt, link);
    elt->thd = t;
    elt->current_owner = NULL;
    elt->state = TH_RUN;
    return elt;
}