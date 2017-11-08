static apr_status_t dbd_sqlite_close(apr_dbd_t * handle)
{
    if (handle->conn) {
        sqlite_close(handle->conn);
        handle->conn = NULL;
    }
    return APR_SUCCESS;
}