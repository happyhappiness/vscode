static int dbd_mysql_select_db(apr_pool_t *pool, apr_dbd_t* handle,
                               const char* name)
{
    return mysql_select_db(handle->conn, name);
}