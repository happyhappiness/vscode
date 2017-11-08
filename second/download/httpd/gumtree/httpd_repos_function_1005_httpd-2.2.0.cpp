static apr_status_t dbd_destruct(void *sql, void *params, apr_pool_t *pool)
{
    ap_dbd_t *rec = sql;
    return apr_dbd_close(rec->driver, rec->handle);
}