static void *odbc_get(const apr_dbd_row_t *row, const int col, 
                      const SQLSMALLINT sqltype)
{
    SQLRETURN rc;
    SQLLEN indicator;
    int state = row->res->colstate[col];
    int options = row->res->apr_dbd->dboptions;

    switch (state) {
    case (COL_UNAVAIL):
        return (void *)-1;
    case (COL_RETRIEVED):
        return NULL;

    case (COL_BOUND):
    case (COL_PRESENT): 
        if (sqltype == row->res->coltypes[col]) {
            /* same type and we already have the data */
            row->res->colstate[col] = COL_RETRIEVED;
            return (row->res->colinds[col] == SQL_NULL_DATA) ? 
                NULL : row->res->colptrs[col];
        }
    }

    /* we need to get the data now */
    if (!(options & SQL_GD_ANY_ORDER)) {
        /* this ODBC driver requires columns to be retrieved in order,
         * so we attempt to get every prior un-gotten non-LOB column
         */
        int i;
        for (i = 0; i < col; i++) {
            if (row->res->colstate[i] == COL_AVAIL) {
                if (IS_LOB(row->res->coltypes[i]))
                       row->res->colstate[i] = COL_UNAVAIL;
                else {
                    odbc_get(row, i, row->res->coltypes[i]);
                    row->res->colstate[i] = COL_PRESENT;
                }
            }
        }
    }

    if ((state == COL_BOUND && !(options & SQL_GD_BOUND)))
        /* this driver won't let us re-get bound columns */
        return (void *)-1;

    /* a LOB might not have a buffer allocated yet - so create one */
    if (!row->res->colptrs[col])
        row->res->colptrs[col] = apr_pcalloc(row->pool, row->res->colsizes[col]);

    rc = SQLGetData(row->res->stmt, col + 1, sqltype, row->res->colptrs[col],
                    row->res->colsizes[col], &indicator);
    CHECK_ERROR(row->res->apr_dbd, "SQLGetData", rc, SQL_HANDLE_STMT, 
                row->res->stmt);
    if (indicator == SQL_NULL_DATA || rc == SQL_NO_DATA)
        return NULL;

    if (SQL_SUCCEEDED(rc)) {
        /* whatever it was originally, it is now this sqltype */
        row->res->coltypes[col] = sqltype;
        /* this allows getting CLOBs in text mode by calling get_entry
         *   until it returns NULL
         */
        row->res->colstate[col] = 
            (rc == SQL_SUCCESS_WITH_INFO) ? COL_AVAIL : COL_RETRIEVED;
        return row->res->colptrs[col];
    }
    else
        return (void *)-1;
}