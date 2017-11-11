static apr_res_t *get_container(apr_reslist_t *reslist)
{
    apr_res_t *res;

    assert(!APR_RING_EMPTY(&reslist->free_list, apr_res_t, link));

    res = APR_RING_FIRST(&reslist->free_list);
    APR_RING_REMOVE(res, link);

    return res;
}