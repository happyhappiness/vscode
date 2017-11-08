static apr_status_t destroy_resource(apr_reslist_t *reslist, apr_res_t *res)
{
    return reslist->destructor(res->opaque, reslist->params, reslist->pool);
}