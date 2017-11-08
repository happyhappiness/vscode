static void *dbd_sqlite_native(apr_dbd_t * handle)
{
    return handle->conn;
}