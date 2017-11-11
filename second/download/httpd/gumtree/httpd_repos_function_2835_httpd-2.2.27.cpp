static int odbc_pselect(apr_pool_t *pool, apr_dbd_t *handle,
                        apr_dbd_results_t **res, apr_dbd_prepared_t *statement,
                        int random, const char **args)
{
    SQLRETURN rc = SQL_SUCCESS;
    int i, argp;

    if (odbc_check_rollback(handle))
        return APR_EGENERAL;

    if (random) {
        rc = SQLSetStmtAttr(statement->stmt, SQL_ATTR_CURSOR_SCROLLABLE,
                            (SQLPOINTER)SQL_SCROLLABLE, 0);
        CHECK_ERROR(handle, "SQLSetStmtAttr (SQL_ATTR_CURSOR_SCROLLABLE)",
                    rc, SQL_HANDLE_STMT, statement->stmt);
    }
    if (SQL_SUCCEEDED(rc)) {
        for (i = argp = 0; i < statement->nargs && SQL_SUCCEEDED(rc); i++) {
            rc = odbc_bind_param(pool, statement, i + 1, statement->types[i],
                                 &argp, (const void **)args, TEXTMODE);
        }
    }
    if (SQL_SUCCEEDED(rc)) {
        rc = SQLExecute(statement->stmt);
        CHECK_ERROR(handle, "SQLExecute", rc, SQL_HANDLE_STMT,
                    statement->stmt);
    }
    if (SQL_SUCCEEDED(rc)) {
        rc = odbc_create_results(handle, statement->stmt, pool, random, res);
        apr_pool_cleanup_register(pool, *res,
                                  odbc_close_results, apr_pool_cleanup_null);
    }
    return APR_FROM_SQL_RESULT(rc);
}