static int odbc_select(apr_pool_t *pool, apr_dbd_t *handle,
                       apr_dbd_results_t **res, const char *statement,
                       int random)
{
    SQLRETURN rc;
    SQLHANDLE hstmt;
    apr_dbd_prepared_t *stmt;
    size_t len = strlen(statement);

    rc = SQLAllocHandle(SQL_HANDLE_STMT, handle->dbc, &hstmt);
    CHECK_ERROR(handle, "SQLAllocHandle (STMT)", rc, SQL_HANDLE_DBC,
                handle->dbc);
    if (!SQL_SUCCEEDED(rc))
        return APR_FROM_SQL_RESULT(rc);
    /* Prepare an apr_dbd_prepared_t for pool cleanup, even though this
    *  is not a prepared statement.  We want the same cleanup mechanism.
    */
    stmt = apr_pcalloc(pool, sizeof(apr_dbd_prepared_t));
    stmt->apr_dbd = handle;
    stmt->dbc = handle->dbc;
    stmt->stmt = hstmt;
    apr_pool_cleanup_register(pool, stmt, odbc_close_pstmt, apr_pool_cleanup_null);
    if (random) {
        rc = SQLSetStmtAttr(hstmt, SQL_ATTR_CURSOR_SCROLLABLE,
                            (SQLPOINTER) SQL_SCROLLABLE, 0);
        CHECK_ERROR(handle, "SQLSetStmtAttr (SQL_ATTR_CURSOR_SCROLLABLE)", rc,
                    SQL_HANDLE_STMT, hstmt);
    }
    if SQL_SUCCEEDED(rc) {
        rc = SQLExecDirect(hstmt, (SQLCHAR *) statement, (SQLINTEGER) len);
        CHECK_ERROR(handle, "SQLExecDirect", rc, SQL_HANDLE_STMT, hstmt);
    }
    if SQL_SUCCEEDED(rc) {
        rc = odbc_create_results(handle, hstmt, pool, random, res);
        apr_pool_cleanup_register(pool, *res, 
                                  odbc_close_results, apr_pool_cleanup_null);
    }
    return APR_FROM_SQL_RESULT(rc);
}