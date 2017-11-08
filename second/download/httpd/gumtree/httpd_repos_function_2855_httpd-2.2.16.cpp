static apr_status_t dbd_sqlite3_check_conn(apr_pool_t *pool,
                                           apr_dbd_t *handle)
{
    return (handle->conn != NULL) ? APR_SUCCESS : APR_EGENERAL;
}