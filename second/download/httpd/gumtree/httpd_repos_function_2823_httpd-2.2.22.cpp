static int odbc_prepare(apr_pool_t *pool, apr_dbd_t *handle,
                        const char *query, const char *label, int nargs,
                        int nvals, apr_dbd_type_e *types,
                        apr_dbd_prepared_t **statement)
{
    SQLRETURN rc;
    size_t len = strlen(query);

    if (odbc_check_rollback(handle))
        return APR_EGENERAL;

    *statement = apr_pcalloc(pool, sizeof(apr_dbd_prepared_t));
    (*statement)->dbc = handle->dbc;
    (*statement)->apr_dbd = handle;
    (*statement)->nargs = nargs;
    (*statement)->nvals = nvals;
    (*statement)->types =
        apr_pmemdup(pool, types, nargs * sizeof(apr_dbd_type_e));
    rc = SQLAllocHandle(SQL_HANDLE_STMT, handle->dbc, &((*statement)->stmt));
    apr_pool_cleanup_register(pool, *statement, 
                              odbc_close_pstmt, apr_pool_cleanup_null);
    CHECK_ERROR(handle, "SQLAllocHandle (STMT)", rc,
                SQL_HANDLE_DBC, handle->dbc);
    rc = SQLPrepare((*statement)->stmt, (SQLCHAR *)query, (SQLINTEGER)len);
    CHECK_ERROR(handle, "SQLPrepare", rc, SQL_HANDLE_STMT,
                (*statement)->stmt);
    return APR_FROM_SQL_RESULT(rc);
}