static apr_status_t dbd_pgsql_check_conn(apr_pool_t *pool,
                                         apr_dbd_t *handle)
{
    if (PQstatus(handle->conn) != CONNECTION_OK) {
        PQreset(handle->conn);
        if (PQstatus(handle->conn) != CONNECTION_OK) {
            return APR_EGENERAL;
        }
    }
    return APR_SUCCESS;
}