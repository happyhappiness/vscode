static apr_dbd_t *odbc_open(apr_pool_t *pool, const char *params, const char **error)
{
    SQLRETURN rc;
    SQLHANDLE hdbc = NULL;
    apr_dbd_t *handle;
    char *err_step;
    int err_htype, i;
    int defaultBufferSize = DEFAULT_BUFFER_SIZE;
    SQLHANDLE err_h = NULL;
    SQLCHAR  *datasource = (SQLCHAR *)"", *user = (SQLCHAR *)"",
             *password = (SQLCHAR *)"";
    int nattrs = 0, *attrs = NULL,  connect = 0;
    intptr_t *attrvals = NULL;

    err_step = "SQLAllocHandle (SQL_HANDLE_DBC)";
    err_htype = SQL_HANDLE_ENV;
    err_h = henv;
    rc = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    if (SQL_SUCCEEDED(rc)) {
        err_step = "Invalid DBD Parameters - open";
        err_htype = SQL_HANDLE_DBC;
        err_h = hdbc;
        rc = odbc_parse_params(pool, params, &connect, &datasource, &user,
                               &password, &defaultBufferSize, &nattrs, &attrs,
                               &attrvals);
    }
    if (SQL_SUCCEEDED(rc)) {
        for (i = 0; i < nattrs && SQL_SUCCEEDED(rc); i++) {
            err_step = "SQLSetConnectAttr (from DBD Parameters)";
            err_htype = SQL_HANDLE_DBC;
            err_h = hdbc;
            rc = SQLSetConnectAttr(hdbc, attrs[i], (SQLPOINTER)attrvals[i], 0);
        }
    }
    if (SQL_SUCCEEDED(rc)) {
        if (connect) {
            SQLCHAR out[1024];
            SQLSMALLINT outlen;

            err_step = "SQLDriverConnect";
            err_htype = SQL_HANDLE_DBC;
            err_h = hdbc;
            rc = SQLDriverConnect(hdbc, NULL, datasource,
                        (SQLSMALLINT)strlen((char *)datasource),
                        out, sizeof(out), &outlen, SQL_DRIVER_NOPROMPT);
        }
        else {
            err_step = "SQLConnect";
            err_htype = SQL_HANDLE_DBC;
            err_h = hdbc;
            rc = SQLConnect(hdbc, datasource,
                        (SQLSMALLINT)strlen((char *)datasource),
                        user, (SQLSMALLINT)strlen((char *)user),
                        password, (SQLSMALLINT)strlen((char *)password));
        }
    }
    if (SQL_SUCCEEDED(rc)) {
        handle = apr_pcalloc(pool, sizeof(apr_dbd_t));
        handle->dbname = apr_pstrdup(pool, (char *)datasource);
        handle->dbc = hdbc;
        handle->pool = pool;
        handle->defaultBufferSize = defaultBufferSize;
        CHECK_ERROR(handle, "SQLConnect", rc, SQL_HANDLE_DBC, handle->dbc);
        handle->default_transaction_mode = 0;
        handle->can_commit = APR_DBD_TRANSACTION_IGNORE_ERRORS;
        SQLGetInfo(hdbc, SQL_DEFAULT_TXN_ISOLATION,
                   &(handle->default_transaction_mode), sizeof(intptr_t), NULL);
        handle->transaction_mode = handle->default_transaction_mode;
        SQLGetInfo(hdbc, SQL_GETDATA_EXTENSIONS ,&(handle->dboptions),
                   sizeof(intptr_t), NULL);
        apr_pool_cleanup_register(pool, handle, odbc_close_cleanup, apr_pool_cleanup_null);
        return handle;
    }
    else {
        apr_dbd_t tmp_dbc;

        tmp_dbc.pool = pool;
        tmp_dbc.dbname = NULL;
        CHECK_ERROR(&tmp_dbc, err_step, rc, err_htype, err_h);
        if (error)
            *error = apr_pstrdup(pool, tmp_dbc.lastError);
        if (hdbc)
            SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
        return NULL;
    }
}