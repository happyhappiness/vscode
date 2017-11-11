static apr_status_t odbc_check_conn(apr_pool_t *pool, apr_dbd_t *handle)
{
    SQLUINTEGER isDead;
    SQLRETURN   rc;

    rc = SQLGetConnectAttr(handle->dbc, SQL_ATTR_CONNECTION_DEAD, &isDead,
                            sizeof(SQLUINTEGER), NULL);
    CHECK_ERROR(handle, "SQLGetConnectAttr (SQL_ATTR_CONNECTION_DEAD)", rc,
                SQL_HANDLE_DBC, handle->dbc);
    /* if driver cannot check connection, say so */
    if (rc != SQL_SUCCESS)
        return APR_ENOTIMPL;

    return (isDead == SQL_CD_FALSE) ? APR_SUCCESS : APR_EGENERAL;
}