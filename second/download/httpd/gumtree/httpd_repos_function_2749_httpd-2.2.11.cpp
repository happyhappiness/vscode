static int odbc_start_transaction(apr_pool_t *pool, apr_dbd_t *handle,
                                  apr_dbd_transaction_t **trans)
{
    SQLRETURN rc = SQL_SUCCESS;

    if (handle->transaction_mode) {
        rc = SQLSetConnectAttr(handle->dbc, SQL_ATTR_TXN_ISOLATION, (void *)
                               handle->transaction_mode, 0);
        CHECK_ERROR(handle, "SQLSetConnectAttr (SQL_ATTR_TXN_ISOLATION)", rc,
                    SQL_HANDLE_DBC, handle->dbc);
    }
    if SQL_SUCCEEDED(rc) {
        /* turn off autocommit for transactions */
        rc = SQLSetConnectAttr(handle->dbc, SQL_ATTR_AUTOCOMMIT,
                               SQL_AUTOCOMMIT_OFF, 0);
        CHECK_ERROR(handle, "SQLSetConnectAttr (SQL_ATTR_AUTOCOMMIT)", rc,
                    SQL_HANDLE_DBC, handle->dbc);
    }
    if SQL_SUCCEEDED(rc) {
        *trans = apr_palloc(pool, sizeof(apr_dbd_transaction_t));
        (*trans)->dbc = handle->dbc;
        (*trans)->apr_dbd = handle;
        handle->can_commit = 1;
    }
    return APR_FROM_SQL_RESULT(rc);
}