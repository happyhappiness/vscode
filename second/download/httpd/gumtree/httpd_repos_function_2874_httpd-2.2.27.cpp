static void *dbd_sqlite3_native(apr_dbd_t *handle)
{
    return handle->conn;
}