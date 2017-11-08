static int odbc_end_transaction(apr_dbd_transaction_t *trans)
{
    SQLRETURN rc;
    int action = (trans->apr_dbd->can_commit != APR_DBD_TRANSACTION_ROLLBACK) 
        ? SQL_COMMIT : SQL_ROLLBACK;

    rc = SQLEndTran(SQL_HANDLE_DBC, trans->dbc, action);
    CHECK_ERROR(trans->apr_dbd, "SQLEndTran", rc, SQL_HANDLE_DBC, trans->dbc);
    if SQL_SUCCEEDED(rc) {
        rc = SQLSetConnectAttr(trans->dbc, SQL_ATTR_AUTOCOMMIT,
                               (SQLPOINTER) SQL_AUTOCOMMIT_ON, 0);
        CHECK_ERROR(trans->apr_dbd, "SQLSetConnectAttr (SQL_ATTR_AUTOCOMMIT)",
                    rc, SQL_HANDLE_DBC, trans->dbc);
    }
    trans->apr_dbd->can_commit = APR_DBD_TRANSACTION_IGNORE_ERRORS;
    return APR_FROM_SQL_RESULT(rc);
}