static apr_status_t odbc_close_env(SQLHANDLE henv)
{   
    SQLRETURN rc;

    rc = SQLFreeHandle(SQL_HANDLE_ENV, henv);
    henv = NULL;
    return APR_FROM_SQL_RESULT(rc);
}