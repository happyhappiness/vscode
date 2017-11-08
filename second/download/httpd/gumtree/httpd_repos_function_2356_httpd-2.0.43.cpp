static apr_status_t destroy_resource(apr_reslist_t *reslist, apr_res_t *res)
{
    apr_status_t rv;

    rv = reslist->destructor(res->opaque, reslist->params, reslist->pool);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    return APR_SUCCESS;
}