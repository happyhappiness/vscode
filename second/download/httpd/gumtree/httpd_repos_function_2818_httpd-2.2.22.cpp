static int odbc_get_row(apr_pool_t *pool, apr_dbd_results_t *res,
                        apr_dbd_row_t **row, int rownum)
{
    SQLRETURN rc;
    char *fetchtype;
    int c;

    *row = apr_pcalloc(pool, sizeof(apr_dbd_row_t));
    (*row)->stmt = res->stmt;
    (*row)->dbc = res->dbc;
    (*row)->res = res;
    (*row)->pool = res->pool;

    /* mark all the columns as needing SQLGetData unless they are bound  */
    for (c = 0; c < res->ncols; c++) {
        if (res->colstate[c] != COL_BOUND) {
            res->colstate[c] = COL_AVAIL;
        }
        /* some drivers do not null-term zero-len CHAR data */
        if (res->colptrs[c])
            *(char *)res->colptrs[c] = 0; 
    }

    if (res->random && (rownum > 0)) {
        fetchtype = "SQLFetchScroll";
        rc = SQLFetchScroll(res->stmt, SQL_FETCH_ABSOLUTE, rownum);
    }
    else {
        fetchtype = "SQLFetch";
        rc = SQLFetch(res->stmt);
    }
    CHECK_ERROR(res->apr_dbd, fetchtype, rc, SQL_HANDLE_STMT, res->stmt);
    (*row)->stmt = res->stmt;
    if (!SQL_SUCCEEDED(rc) && !res->random) {
        /* early close on any error (usually SQL_NO_DATA) if fetching
         * sequentially to release resources ASAP
         */
        odbc_close_results(res);
        return -1;
    }
    return SQL_SUCCEEDED(rc) ? 0 : -1;
}