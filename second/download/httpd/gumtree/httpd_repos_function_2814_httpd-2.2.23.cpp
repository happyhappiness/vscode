static int odbc_set_dbname(apr_pool_t*pool, apr_dbd_t *handle,
                           const char *name)
{
    if (apr_strnatcmp(name, handle->dbname)) {
        return APR_EGENERAL;        /* It's illegal to change dbname in ODBC */
    }
    CHECK_ERROR(handle, "set_dbname (no-op)", SQL_SUCCESS, SQL_HANDLE_DBC,
                handle->dbc);
    return APR_SUCCESS;             /* OK if it's the same name */
}