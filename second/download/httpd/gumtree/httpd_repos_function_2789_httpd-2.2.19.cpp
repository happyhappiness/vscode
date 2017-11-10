static apr_status_t odbc_close_pstmt(void *s)
{   
    SQLRETURN rc = APR_SUCCESS;
    apr_dbd_prepared_t *statement = s;

    /* stmt is closed if connection has already been closed */
    if (statement) {
        SQLHANDLE hstmt = statement->stmt;

        if (hstmt && statement->apr_dbd && statement->apr_dbd->dbc) {
            rc = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        }
        statement->stmt = NULL;
    }
    return APR_FROM_SQL_RESULT(rc);
}