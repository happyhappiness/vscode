static int odbc_query(apr_dbd_t *handle, int *nrows, const char *statement)
{
    SQLRETURN rc;
    SQLHANDLE hstmt = NULL;
    size_t len = strlen(statement);

    if (odbc_check_rollback(handle))
        return APR_EGENERAL;

    rc = SQLAllocHandle(SQL_HANDLE_STMT, handle->dbc, &hstmt);
    CHECK_ERROR(handle, "SQLAllocHandle (STMT)", rc, SQL_HANDLE_DBC,
                handle->dbc);
    if (!SQL_SUCCEEDED(rc))
        return APR_FROM_SQL_RESULT(rc);

    rc = SQLExecDirect(hstmt, (SQLCHAR *)statement, (SQLINTEGER)len);
    CHECK_ERROR(handle, "SQLExecDirect", rc, SQL_HANDLE_STMT, hstmt);

    if (SQL_SUCCEEDED(rc)) {
        SQLLEN rowcount;

        rc = SQLRowCount(hstmt, &rowcount);
        *nrows = (int)rowcount;
        CHECK_ERROR(handle, "SQLRowCount", rc, SQL_HANDLE_STMT, hstmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return APR_FROM_SQL_RESULT(rc);
}