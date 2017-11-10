static int odbc_transaction_mode_set(apr_dbd_transaction_t * trans, int mode)
{
    SQLRETURN rc;

    int legal = (SQL_TXN_READ_UNCOMMITTED | SQL_TXN_READ_COMMITTED
                 | SQL_TXN_REPEATABLE_READ | SQL_TXN_SERIALIZABLE);

    if ((mode & legal) != mode)
        return APR_EGENERAL;

    trans->apr_dbd->transaction_mode = mode;
    rc = SQLSetConnectAttr(trans->dbc, SQL_ATTR_TXN_ISOLATION, 
                           (void *) mode, 0);
    CHECK_ERROR(trans->apr_dbd, "SQLSetConnectAttr (SQL_ATTR_TXN_ISOLATION)",
                rc, SQL_HANDLE_DBC, trans->dbc);
    return APR_FROM_SQL_RESULT(rc);
}