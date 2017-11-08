static apr_status_t dbd_mysql_check_conn(apr_pool_t *pool,
                                         apr_dbd_t *handle)
{
    return mysql_ping(handle->conn) ? APR_EGENERAL : APR_SUCCESS;
}