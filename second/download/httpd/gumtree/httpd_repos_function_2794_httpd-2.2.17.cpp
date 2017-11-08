static SQLRETURN odbc_create_results(apr_dbd_t * handle, SQLHANDLE hstmt,
                                     apr_pool_t * pool, const int random,
                                     apr_dbd_results_t ** res)
{
    SQLRETURN rc;
    SQLSMALLINT ncols;

    *res = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
    (*res)->stmt = hstmt;
    (*res)->dbc = handle->dbc;
    (*res)->pool = pool;
    (*res)->random = random;
    (*res)->apr_dbd = handle;
    rc = SQLNumResultCols(hstmt, &ncols);
    CHECK_ERROR(handle, "SQLNumResultCols", rc, SQL_HANDLE_STMT, hstmt);
    (*res)->ncols = ncols;

    if SQL_SUCCEEDED(rc) {
        int i;

        (*res)->colnames = apr_pcalloc(pool, ncols * sizeof(char *));
        (*res)->colptrs = apr_pcalloc(pool, ncols * sizeof(void *));
        (*res)->colsizes = apr_pcalloc(pool, ncols * sizeof(SQLINTEGER));
        (*res)->coltypes = apr_pcalloc(pool, ncols * sizeof(SQLSMALLINT));
        (*res)->colinds = apr_pcalloc(pool, ncols * sizeof(SQLLEN));
        (*res)->colstate = apr_pcalloc(pool, ncols * sizeof(int));
        (*res)->ncols = ncols;

        for (i = 0 ; i < ncols ; i++)
            odbc_set_result_column(i, (*res), hstmt);
        }
    return rc;
}