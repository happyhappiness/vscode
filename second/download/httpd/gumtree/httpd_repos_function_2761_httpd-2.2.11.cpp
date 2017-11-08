static int odbc_pquery(apr_pool_t * pool, apr_dbd_t * handle, int *nrows,
                       apr_dbd_prepared_t * statement, const char **args)
{
    SQLRETURN rc = SQL_SUCCESS;
    int i, argp;

    for (i = argp = 0; i < statement->nargs && SQL_SUCCEEDED(rc); i++) {
        rc = odbc_bind_param(pool, statement, i + 1, statement->types[i],
                             &argp, (const void **) args, TEXTMODE);
    }
    if (SQL_SUCCEEDED(rc)) {
        rc = SQLExecute(statement->stmt);
        CHECK_ERROR(handle, "SQLExecute", rc, SQL_HANDLE_STMT,
                    statement->stmt);
        }
    if (SQL_SUCCEEDED(rc)) {
        rc = SQLRowCount(statement->stmt, (SQLINTEGER *) nrows);
        CHECK_ERROR(handle, "SQLRowCount", rc, SQL_HANDLE_STMT,
                    statement->stmt);
        }
    return APR_FROM_SQL_RESULT(rc);
}