static int indexing_comp(void *a, void *b)
{
    apr_time_t t1 = (apr_time_t) (((timer_event_t *) a)->when);
    apr_time_t t2 = (apr_time_t) (((timer_event_t *) b)->when);
    AP_DEBUG_ASSERT(t1);
    AP_DEBUG_ASSERT(t2);
    return ((t1 < t2) ? -1 : ((t1 > t2) ? 1 : 0));
}