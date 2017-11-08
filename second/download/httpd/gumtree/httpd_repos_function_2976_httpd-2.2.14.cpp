static void *dbd_mysql_native(apr_dbd_t *handle)
{
    return handle->conn;
}