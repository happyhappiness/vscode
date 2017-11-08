static void *dbd_pgsql_native(apr_dbd_t *handle)
{
    return handle->conn;
}