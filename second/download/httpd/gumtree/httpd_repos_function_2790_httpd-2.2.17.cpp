static apr_status_t odbc_close(apr_dbd_t *handle)
{
    SQLRETURN rc = SQL_SUCCESS;

    if (handle->dbc) {
        rc = SQLDisconnect(handle->dbc);
        CHECK_ERROR(handle, "SQLDisconnect", rc, SQL_HANDLE_DBC, handle->dbc);
        rc = SQLFreeHandle(SQL_HANDLE_DBC, handle->dbc);
        CHECK_ERROR(handle, "SQLFreeHandle (DBC)", rc, SQL_HANDLE_ENV, henv);
        handle->dbc = NULL;
    }
    return APR_FROM_SQL_RESULT(rc);
}