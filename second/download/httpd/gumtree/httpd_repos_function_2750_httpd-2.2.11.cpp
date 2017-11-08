static int odbc_end_transaction(apr_dbd_transaction_t *trans)
{
    SQLRETURN rc;

    rc = SQLEndTran(SQL_HANDLE_DBC, trans->dbc, SQL_COMMIT);
    CHECK_ERROR(trans->apr_dbd, "SQLEndTran", rc, SQL_HANDLE_DBC, trans->dbc);
    if SQL_SUCCEEDED(rc) {
        rc = SQLSetConnectAttr(trans->dbc, SQL_ATTR_AUTOCOMMIT,
                               (SQLPOINTER) SQL_AUTOCOMMIT_ON, 0);
        CHECK_ERROR(trans->apr_dbd, "SQLSetConnectAttr (SQL_ATTR_AUTOCOMMIT)",
                    rc, SQL_HANDLE_DBC, trans->dbc);
    }
    return APR_FROM_SQL_RESULT(rc);
}