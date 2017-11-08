static int dbd_sqlite3_start_transaction(apr_pool_t *pool,
                                         apr_dbd_t *handle,
                                         apr_dbd_transaction_t **trans)
{
    int ret = 0;
    int nrows = 0;

    ret = dbd_sqlite3_query(handle, &nrows, "BEGIN");
    if (!*trans) {
        *trans = apr_pcalloc(pool, sizeof(apr_dbd_transaction_t));
        (*trans)->handle = handle;
        handle->trans = *trans;
    }

    return ret;
}