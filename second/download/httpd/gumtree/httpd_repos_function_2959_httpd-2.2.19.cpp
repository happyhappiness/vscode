static int dbd_pgsql_start_transaction(apr_pool_t *pool, apr_dbd_t *handle,
                                       apr_dbd_transaction_t **trans)
{
    int ret = 0;
    PGresult *res;

    /* XXX handle recursive transactions here */

    res = PQexec(handle->conn, "BEGIN TRANSACTION");
    if (res) {
        ret = PQresultStatus(res);
        if (dbd_pgsql_is_success(ret)) {
            ret = 0;
            if (!*trans) {
                *trans = apr_pcalloc(pool, sizeof(apr_dbd_transaction_t));
            }
        }
        PQclear(res);
        (*trans)->handle = handle;
        handle->trans = *trans;
    }
    else {
        ret = PGRES_FATAL_ERROR;
    }
    return ret;
}