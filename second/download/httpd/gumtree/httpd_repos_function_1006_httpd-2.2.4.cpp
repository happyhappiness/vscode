static apr_status_t dbd_destruct(void *sql, void *params, apr_pool_t *pool)
{
    return dbd_close(sql);
}