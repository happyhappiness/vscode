static void push_resource(apr_reslist_t *reslist, apr_res_t *resource)
{
    APR_RING_INSERT_HEAD(&reslist->avail_list, resource, apr_res_t, link);
    resource->freed = apr_time_now();
    reslist->nidle++;
}