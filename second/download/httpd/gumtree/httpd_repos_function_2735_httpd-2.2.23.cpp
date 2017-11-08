static apr_status_t create_resource(apr_reslist_t *reslist, apr_res_t **ret_res)
{
    apr_status_t rv;
    apr_res_t *res;

    res = get_container(reslist);

    rv = reslist->constructor(&res->opaque, reslist->params, reslist->pool);

    *ret_res = res;
    return rv;
}