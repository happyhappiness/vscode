static apr_status_t dbd_freetds_check_conn(apr_pool_t *pool,
                                           apr_dbd_t *handle)
{
    if (dbdead(handle->proc)) {
        /* try again */
        dbclose(handle->proc);
        handle->proc = freetds_open(handle->pool, handle->params, NULL);
        if (!handle->proc || dbdead(handle->proc)) {
            return APR_EGENERAL;
        }
    }
    /* clear it, in case this is called in error handling */
    dbcancel(handle->proc);
    return APR_SUCCESS;
}