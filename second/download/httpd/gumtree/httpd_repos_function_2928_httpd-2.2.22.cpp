static int dbd_sqlite_start_transaction(apr_pool_t * pool, apr_dbd_t * handle,
                                        apr_dbd_transaction_t ** trans)
{
    int ret, rows;

    ret = dbd_sqlite_query(handle, &rows, "BEGIN TRANSACTION");
    if (ret == 0) {
        if (!*trans) {
            *trans = apr_pcalloc(pool, sizeof(apr_dbd_transaction_t));
        }
        (*trans)->handle = handle;
        handle->trans = *trans;
    }
    else {
        ret = -1;
    }
    return ret;
}