static int odbc_num_tuples(apr_dbd_results_t *res)
{
    SQLRETURN rc;
    SQLLEN nrows;

    rc = SQLRowCount(res->stmt, &nrows);
    CHECK_ERROR(res->apr_dbd, "SQLRowCount", rc, SQL_HANDLE_STMT, res->stmt);
    return SQL_SUCCEEDED(rc) ? (int)nrows : -1;
}