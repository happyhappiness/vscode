static void free_container(apr_reslist_t *reslist, apr_res_t *container)
{
    APR_RING_INSERT_TAIL(&reslist->free_list, container, apr_res_t, link);
}