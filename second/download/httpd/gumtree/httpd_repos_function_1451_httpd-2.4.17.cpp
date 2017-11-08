static apr_status_t dbd_destruct(void *data, void *params, apr_pool_t *pool)
{
    dbd_group_t *group = params;

    if (!group->destroyed) {
        ap_dbd_t *rec = data;

        apr_pool_destroy(rec->pool);
    }

    return APR_SUCCESS;
}