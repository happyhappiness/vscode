static int odbc_pbquery(apr_pool_t *pool, apr_dbd_t *handle, int *nrows,
                        apr_dbd_prepared_t *statement, const void **args)
{
    SQLRETURN rc = SQL_SUCCESS;
    int i, argp;

    if (odbc_check_rollback(handle))
        return APR_EGENERAL;

    for (i = argp = 0; i < statement->nargs && SQL_SUCCEEDED(rc); i++)
        rc = odbc_bind_param(pool, statement, i + 1, statement->types[i],
                             &argp, args, BINARYMODE);

    if (SQL_SUCCEEDED(rc)) {
        rc = SQLExecute(statement->stmt);
        CHECK_ERROR(handle, "SQLExecute", rc, SQL_HANDLE_STMT,
                    statement->stmt);
    }
    if (SQL_SUCCEEDED(rc)) {
        SQLLEN rowcount;

        rc = SQLRowCount(statement->stmt, &rowcount);
        *nrows = (int)rowcount;
        CHECK_ERROR(handle, "SQLRowCount", rc, SQL_HANDLE_STMT,
                    statement->stmt);
    }
    return APR_FROM_SQL_RESULT(rc);
}