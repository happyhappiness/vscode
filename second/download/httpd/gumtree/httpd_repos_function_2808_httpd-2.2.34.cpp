static int dbd_freetds_start_transaction(apr_pool_t *pool, apr_dbd_t *handle,
                                         apr_dbd_transaction_t **trans)
{
    int dummy;

    /* XXX handle recursive transactions here */

    handle->err = freetds_exec(handle->proc, "BEGIN TRANSACTION", 0, &dummy);

    if (dbd_freetds_is_success(handle->err)) {
        if (!*trans) {
            *trans = apr_pcalloc(pool, sizeof(apr_dbd_transaction_t));
        }
        (*trans)->handle = handle;
        handle->trans = *trans;
        return 0;
    }

    return 1;
}