static apr_status_t odbc_close_results(void *d)
{
    apr_dbd_results_t *dbr = (apr_dbd_results_t *)d;
    SQLRETURN rc = SQL_SUCCESS;
    
    if (dbr && dbr->apr_dbd && dbr->apr_dbd->dbc) {
    	if (!dbr->isclosed)
            rc = SQLCloseCursor(dbr->stmt);
    	dbr->isclosed = 1;
    }
    return APR_FROM_SQL_RESULT(rc);
}