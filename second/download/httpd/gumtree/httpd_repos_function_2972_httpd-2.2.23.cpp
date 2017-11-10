static apr_status_t dbd_pgsql_close(apr_dbd_t *handle)
{
    PQfinish(handle->conn);
    return APR_SUCCESS;
}