static apr_status_t dbd_sqlite_check_conn(apr_pool_t * pool,
                                          apr_dbd_t * handle)
{
    if (handle->conn == NULL)
        return -1;
    return APR_SUCCESS;
}