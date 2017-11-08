static const char *odbc_get_name(const apr_dbd_results_t *res, int col)
{
    SQLRETURN rc;
    char buffer[MAX_COLUMN_NAME];
    SQLSMALLINT colnamelength, coltype, coldecimal, colnullable;
    SQLULEN colsize;

    if (col >= res->ncols)
        return NULL;            /* bogus column number */
    if (res->colnames[col] != NULL)
        return res->colnames[col];      /* we already retrieved it */
    rc = SQLDescribeCol(res->stmt, col + 1,
                        (SQLCHAR *)buffer, sizeof(buffer), &colnamelength,
                        &coltype, &colsize, &coldecimal, &colnullable);
    CHECK_ERROR(res->apr_dbd, "SQLDescribeCol", rc,
                SQL_HANDLE_STMT, res->stmt);
    res->colnames[col] = apr_pstrdup(res->pool, buffer);
    return res->colnames[col];
}